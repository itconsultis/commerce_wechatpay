<?php

/**
 * @file
 * API documentation for the Commerce Wechatpay module.
 */

/**
 * Allows modules to alter main handler class name. You can extend the default class
 * and put your own class name here to use it.
 *
 * By default is "CommerceWechatpay"
 *
 * @param string $class_name
 *   Our main handler class name
 *
 * @see commerce_wechatpay_get_handler_class()
 */
function hook_commerce_wechatpay_class_name_alter(&$class_name) {
  $class_name = 'YOUR_OWN_HANDLER_CLASS';
}

/**
 * Allows modules to alter process javascript handler function name.
 * The function must bind to window where the module can call it globally.
 *
 * By default is "proceedWXPayment"
 *
 * @param string $js_function_name
 *   Our js handler name
 *
 * @see commerce_wechatpay_get_js_function()
 */
function hook_commerce_wechatpay_javascript_handler_name_alter(&$js_function_name) {
  $js_function_name = 'YOUR_OWN_JS_PROCESS_HANDLER_FUNCTION';
}

/**
 * Allows modules to alter wait&check javascript handler function name which waits for user to scan and redirect to successful page when it's done.
 * The function must bind to window where the module can call it globally.
 *
 * By default is "qrCheckingLoop"
 *
 * @param string $js_function_name
 *   Our js handler name
 *
 * @see commerce_wechatpay_get_js_function()
 */
function hook_commerce_wechatpay_javascript_checking_loop_handler_name_alter(&$js_function_name) {
  $js_function_name = 'YOUR_OWN_JS_CHECKING_HANDLER_FUNCTION';
}

/**
 * Allows modules to alter defined Wechatpay API transaction parameters and the data sending to JS.
 *
 * @param array $data
 *   Array contains data about to send to Wechat
 * @param array $payment_method_instance
 *   Instance of commerce payment method, contains wechatpay credentials
 * @param stdClass $order
 *   If available, the order object for which the payment should be processed.
 *
 * @see commerce_wechatpay_checkout_handler()
 */
function hook_commerce_wechatpay_data_alter(&$data, $payment_method_instance, $order) {
  // change wehcat order information
  $data['order_body'] = 'NEW_WECHAT_ORDER_TITLE';
  $data['amountToWechat'] = '10000';

  // redirect success order to user profile page
  $data['return_success_url'] = url('user', array('absolute' => TRUE));

}

/**
 * Allows modules to alter transaction data before saving it into Drupal after a successful payment.
 *
 * @param object $transaction
 *   Obejct contains data about to save
 * @param array $feedback_transaction
 *   feedbacks heard form Wechat
 * @param stdClass $order
 *   If available, the order object for which the transaction should be processed.
 * @param array $payment_method_instance
 *   Instance of commerce payment method, contains wechatpay credentials
 *
 * @see commerce_wechatpay_notify_success_handler()
 */
function hook_commerce_wechatpay_transaction_presave_alter(&$transaction, $feedback_transaction, $order, $payment_method_instance) {
  $transaction->currency_code = 'NEW_CURRENCY_CODE';
  $transaction->remote_id = 'NEW_TRANSACTION_ID';
}

