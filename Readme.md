gst-launch-1.0 videotestsrc ! video/x-raw, width=1920, height=1080 ! autovideosink
gst-launch-1.0 videotestsrc pattern=18 ! video/x-raw, width=1200, height=1600, framerate=60/1 ! autovideosink //顯示測試螢幕


@parm   1 確認
        2 取消
        3 往左
        4 往右

print 首頁                status 0
    輸入3或是4
        進入status 1

print 選取頁面            status 1
    輸入3
        print 左圖
    輸入4
        print 右圖
    輸入1
        進入status 2
    輸入2
        進入status 0

print 時間頁面              status 2
    輸入3
        減少時間
    輸入4
        增加時間
    輸入1
        進入status 3
    輸入2
        進入status 1

print 選擇付款方式          status 3
    輸入3
        print 卡片付款圖
    輸入4
        print QR code付款
    輸入1
        進入status 4
    輸入2
        進入status 2

print 付款圖                status 4
    if 付款方式等於0
        print 卡片付款
    else if 付款方式等於1
        print QRCode 付款