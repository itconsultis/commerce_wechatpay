Payment method: Wechatpay for drupal commerce
==============

This moudle is using the v3 interface of wechatpay.
本模块使用的是微信支付v3接口。

SDK taken from "overtrue/wechat" which is a very cool and written in PHP:
使用本模块前请前往下载overtrue的wechatSDK，是一个非常酷的微信公众平台SDK包:

Download: https://github.com/overtrue/wechat
Docs: https://github.com/overtrue/wechat/wiki/%E5%BE%AE%E4%BF%A1%E6%94%AF%E4%BB%98

### Extra stuff...
The reason didn't use Wechatpay official sdk is because they put all credentials (APPID, Secret, MCHID, key) in "WxPay.Config.php", WTF...TT