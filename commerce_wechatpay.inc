<?php

use Overtrue\Wechat\Payment;
use Overtrue\Wechat\Payment\Order;
use Overtrue\Wechat\Payment\Business;
use Overtrue\Wechat\Payment\UnifiedOrder;
use Overtrue\Wechat\Payment\Notify;

use Overtrue\Wechat\Auth;

/**
 * Class CommerceWechatpay
 * Main handler class for Commerce wechatpay, you can extend this class
 * and set your own name using hook_commerce_wechatpay_class_name_alter()
 *
 * @see hook_commerce_wechatpay_class_name_alter()
 * @see commerce_wechatpay_get_handler_class()
 *
 */
Class CommerceWechatpay {

  protected $appId;
  protected $appSecret;
  protected $mchId;
  protected $mchKey;
  protected $jsParm;
  protected $transaction_info;
  protected $notify_obj;

  public function __construct($appId, $appSecret, $mchId, $mchKey){
    $this->appId = $appId;
    $this->appSecret = $appSecret;
    $this->mchId = $mchId;
    $this->mchKey = $mchKey;
    return $this;
  }

  /**
   * Prepare all parameters and send to Wechat
   */
  public function proceed($order_num, $oder_name, $price, $notify_url){
    /**
     * Set business
     */
    $business = new Business($this->appId, $this->appSecret, $this->mchId, $this->mchKey);

    /**
     * Get openid
     */
    $auth = new Auth($this->appId, $this->appSecret);

    if (empty($_SESSION['wechat_logged_user'])) {
      $user = $auth->authorize(null, 'snsapi_base', 'STATE');
      $_SESSION['wechat_logged_user'] = $user->all();
    } else {
      $user = $_SESSION['wechat_logged_user'];
    }
    $openid = $user['openid'];


    /**
     * Create order
     */
    $order = new Order();
    $order->body = $oder_name;
    $order->out_trade_no = $this->orderId2outTradeNo($order_num);
    $order->total_fee = $price;    // 单位为 “分”, 字符串类型
    $order->openid = $openid;
    $order->notify_url = $notify_url;

    /**
     * Process Unified order
     */
    $unifiedOrder = new UnifiedOrder($business, $order);

    /**
     * Generate payment parameters
     */
    $payment = new Payment($unifiedOrder);
    $this->jsParm = $payment->getConfig();

  }

  public function proceed_qrpay($order_num, $oder_name, $price, $notify_url) {
    /**
     * Set business
     */
    $business = new Business($this->appId, $this->appSecret, $this->mchId, $this->mchKey);

    /**
     * Create order
     */
    $order = new Order();
    $order->trade_type = 'NATIVE';
    $order->body = $oder_name;
    $order->out_trade_no = $this->orderId2outTradeNo($order_num);
    $order->total_fee = $price;    // 单位为 “分”, 字符串类型
    $order->notify_url = $notify_url;

    /**
     * Process Unified order
     */
    $unifiedOrder = new UnifiedOrder($business, $order);
    $uni_res = $unifiedOrder->getResponse();

    if (empty($uni_res["code_url"])) {
      return false;
    }

    return $uni_res["code_url"];
  }

  /**
   * Generate out trade number from order_id, feel free to extend
   */
  public function orderId2outTradeNo($order_num) {
    $out_trade_no = $order_num;
    return $out_trade_no;
  }

  /**
   * Get order_id from out trade number, feel free to extend
   */
  public function outTradeNo2orderId($out_trade_no) {
    $order_num = $out_trade_no;
    return $order_num;
  }

  public function getJsParm($order_num, $oder_name, $price = 1, $notify_url, $sendOpenId = TRUE){
    $this->proceed($order_num, $oder_name, $price, $notify_url, $sendOpenId);
    return $this->jsParm;
  }

  /**
   * Receive notification and verify it
   *
   * @return bool|array
   */
  public function receiveNotify() {

    $transaction = $this->getNotifyInstance()->verify();

    if (!$transaction) {
      return false;
    }

    $this->transaction_info = $transaction->all();

    return $transaction->all();
  }

  public function getTransactionInfo() {
    return $this->transaction_info;
  }

  public function getReplyReceived() {
    return $this->getNotifyInstance()->reply();
  }

  public function getNotifyInstance() {
    if (!$this->notify_obj) {
      $this->notify_obj = new Notify($this->appId, $this->appSecret, $this->mchId, $this->mchKey);
    }
    return $this->notify_obj;
  }

}