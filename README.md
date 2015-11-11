Commerce Wechatpay
==============

Wechat payment method (微信支付模块) for Drupal Commerce

Also available in [Drupal sandbox](https://www.drupal.org/sandbox/yuhao6066/2612324) now

## Requirements

1. SDK package [overtrue/wechat](https://github.com/overtrue/wechat)

  在安装本模块前，请下载overtrue的wechatSDK，并放入"libraries"文件夹中
  
  Please download SDK package and put inside "libraries" folder before install this module

  ```shell
  cd PATH_TO_DRUPAL/sites/all/libraries
  git clone https://github.com/overtrue/wechat.git
  mv wechat/ overtrue_wechat/
  ```
  
  更多关于此SDK的信息请[参考文档](https://github.com/overtrue/wechat/wiki/%E5%BE%AE%E4%BF%A1%E6%94%AF%E4%BB%98)
  
  More inforamtion about overtrue_wechat please [see docs](https://github.com/overtrue/wechat/wiki/%E5%BE%AE%E4%BF%A1%E6%94%AF%E4%BB%98)

## Installation

1. Follow the default way of set-up a payment module for Drupal Commerce, take a look at [commerce_paypal](https://www.drupal.org/project/commerce_paypal) installation if you don't understand.

2. Configure Wechat payment (only for Merchat pay - 公众号支付)

  Set an authorized URL alias in Wechat back-office, [image example](https://raw.githubusercontent.com/tomzhu6066/commerce_wechatpay/master/commerce_wechatpay_configuration.jpg)

  在微信公众平台的后台，将如下地址设置为一个支付授权目录, [图片示例](https://raw.githubusercontent.com/tomzhu6066/commerce_wechatpay/master/commerce_wechatpay_configuration.jpg)

  ```
  http://YOUR_DOMAIN.COM/ALIAS_TO_DRUPAL_ROOT/commerce_wechatpay/checkout/
  ```

## Payment methods

1. Merchant pay (jsapi)([公众号支付](https://pay.weixin.qq.com/wiki/doc/api/jsapi.php?chapter=7_1))

  Requires opening payment page in Wechat browser, otherwise will return error. This method is good when developing all-browse-in-wechat web page.

2. QR code pay (native)([扫码支付](https://pay.weixin.qq.com/wiki/doc/api/native.php?chapter=6_1))

  (本模块使用的是扫码支付的支付模式二，所以无需设置扫码支付的支付回调URL)

  (This module uses wechat scan&pay mode 2, so no need to set redirect URL on scan&pay settings area)

  Provides a QR code image when going to the off-site payment gateway, allows user to scan the QR code and pay directly in Wechat. If opening payment page in Wechat browser, user can long-press the QRcode to pay (wechat build-in feature) but will not be returned back to successful page.
  
3. Mixed with Merchat pay and QR code pay (Comming soon)
  
  By detecting user browser information, lead user to one of the above method. This method is still under development.

## API docs

##### Overwrite main class handler
  
  1. use the API to change to your class first
  ```php
  function YOUR_MODULE_commerce_wechatpay_class_name_alter(&$class_name) {
    $class_name = 'YOUR_OWN_HANDLER_CLASS';
  }
  ```
  
  2. then define your class, it's recommand if you extend from the original class
  ```php
  Class YOUR_OWN_HANDLER_CLASS extends CommerceWechatpay {
    public function orderId2outTradeNo ($order_num)
    {
      // I want my own way for transfering order_id to out_trade_no
      return md5('some_secret_string'.md5($order_num));
    }
    
    // other overwritten, blabla
  }
  ```

##### Overwrite javascript process handler

  1. use the API to change to your js process handler first
  ```php
  function YOUR_MODULE_commerce_wechatpay_javascript_handler_name_alter(&$js_function_name) {
    $js_function_name = 'YOUR_OWN_JS_HANDLER_FUNCTION';
  }
  ```
  
  2. then define your javascript function
  ```js
  window.YOUR_OWN_JS_HANDLER_FUNCTION = function(configs, return_success_url, return_failure_url)
  {
    // some overwritten, blabla
  }
  ```

##### Overwrite QRcode generator

  (We are currently using the qrcode generator API from [api.qrserver.com](https://qrserver.com))

  1. use the API to change to your generator first
  ```php
  function YOUR_MODULE_wechatpay_qr_generator_alter(&$qr_generator) {
    $qr_generator = 'YOUR_GENERATOR_FUNCTION_NAME';
  }
  ```
  
  2. then define your own PHP qr generation function
  ```php
  function YOUR_GENERATOR_FUNCTION_NAME($content)
  {
    // some little tip here: you can use phpqrcode plugin to generate with PHP, 
    // which save A LOT!! times instead of requesting outside resouces like GOOGLE QRcode
    // @see https://github.com/t0k4rt/phpqrcode
    include_once 'LIBRARIES_FOLDER/t0k4rt_phpqrcode/qrlib.php';
    QRcode::png($content, null);

  }
  ```

## Extra stuff...

I'm sorry to say but the reason I didn't use Wechatpay official sdk is because they put all credentials (APPID, Secret, MCHID, key) in "WxPay.Config.php", WTF...TT
