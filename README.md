Commerce Wechatpay
==============

This moudle is using the v3 interface of wechatpay.

本模块使用的是微信支付v3接口。

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

## Features

1. Merchat pay (jsapi)([公众号支付](https://pay.weixin.qq.com/wiki/doc/api/jsapi.php?chapter=7_1))

  Requires opening payment page in Wechat browser, otherwise will return error. This method is good when developing all-browse-in-wechat web page.

2. QR code pay (native)([扫码支付](https://pay.weixin.qq.com/wiki/doc/api/native.php?chapter=6_1))

  Provides a QR code image when going to the off-site payment gateway, allows user to scan the QR code and pay directly in Wechat. If opening payment page in Wechat browser, user can long-press the QRcode to pay (wechat build-in feature) but will not be returned back to successful page.
  
3. Mixed with Merchat pay and QR code pay (Comming soon)
  
  By detecting user browser information, lead user to one of the above method. This method is still under development.

## Extra stuff...

I'm sorry to say but the reason I didn't use Wechatpay official sdk is because they put all credentials (APPID, Secret, MCHID, key) in "WxPay.Config.php", WTF...TT
