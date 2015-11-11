(function ($) {

    /**
     * Poll the condition function for ttl milliseconds, and callback when the
     * condition function returns a truthy value.
     * @param {Function} condition - a function that returns a truthy or falsy value
     * @param {Function} done - invoked when the condition function returns true
     * @param {Number} ttl - number of milliseconds before polling aborts
     * @param {Number} frequency - number of milliseconds between polling iterations
     * @return void
     */
    var when = function(condition, done, ttl, frequency) {
        ttl = ttl || 1000;
        frequency = frequency || 10;

        var abort = function() {
            clear_timeouts();
            done(new Error('operation timed out'));
        };

        var abort_timeout = setTimeout(abort, ttl);

        var clear_timeouts = function() {
            clearTimeout(abort_timeout);
            clearTimeout(poll_timeout);
        };

        var poll_timeout;

        var poll = function() {
            if (condition()) {
                clear_timeouts();
                done(false);
            }
            else {
                poll_timeout = setTimeout(poll, frequency);
            }
        };

        poll();

    };

    /**
     * Javascript handler function to use Wechat JS to control payment
     * If you need to use another function, see hook_commerce_wechatpay_class_name_alter()
     *
     * @param (json string) configs
     *   The configuration parameters which Wechatpay need
     * @param (string) return_success_url
     * @param (string) return_failure_url
     *
     * @see hook_commerce_wechatpay_class_name_alter()
     * @see commerce_wechatpay_get_js_function()
     */
    window.proceedWXPayment = function(configs, return_success_url, return_failure_url) {

        var pay = function() {
            WeixinJSBridge.invoke('getBrandWCPayRequest', configs, function (res) {
                switch (res.err_msg) {
                    case 'get_brand_wcpay_request:cancel':
                        alert('用户取消支付！');
                        window.location = return_failure_url;
                        break;
                    case 'get_brand_wcpay_request:fail':
                        alert('支付失败！');
                        //alert(res.err_desc);
                        window.location = return_failure_url;
                        break;
                    case 'get_brand_wcpay_request:ok':
                        alert('支付成功！');
                        window.location = return_success_url;
                        break;
                    default:
                        //alert(JSON.stringify(res));
                        break;
                }
            });
        };

        var weixin_bridge_ready = function() {
            if(typeof WeixinJSBridge !== 'undefined')
                return true;
            else
                return false;
        };

        // wait 10 sec for WeixinJSBridge loaded from DOM
        when(weixin_bridge_ready, function(err) {
            if (!err) {
                pay();
            }
        }, 10000);
    };

    window.qrCheckingLoop = function(url, return_success_url){

        var flag = false;

        var request = function () {
            //console.log('requesting...');
            jQuery.ajax({
                url: url,
                success: function(data){
                    console.log(data);
                    if(typeof data != 'undefined' && data.status == 1){
                        flag = true;
                    }
                }
            });

            return false;
        };

        var weixin_payment_status_updated = function() {
            //console.log('checking...');
           return flag;
        };

        // send request every 2 seconds
        when(request, function(err) {}, 60000, 2000);

        // wait 60 sec for success status
        when(weixin_payment_status_updated, function(err) {
            if (!err) {
                alert('支付成功！');
                window.location = return_success_url;
            }
        }, 60000, 500);
    }

})(jQuery);