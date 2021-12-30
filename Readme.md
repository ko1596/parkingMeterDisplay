``` bash
gst-launch-1.0 videotestsrc ! video/x-raw, width=1920, height=1080 ! autovideosink
gst-launch-1.0 videotestsrc pattern=18 ! video/x-raw, width=1200, height=1600, framerate=60/1 ! autovideosink //顯示測試螢幕

gst-launch-1.0 -q filesrc location=6.png ! pngdec ! imagefreeze ! videoconvert ! video/x-raw, framerate=1/1 ! autovideosink
```

# command input

* command 1 -> Empty
* command 2 -> Parking
* command 3 -> Shooting card
* command 4 -> Shooting card 1 card
* command 5 -> Verifying 
* command 6 -> Verify success
* command 7 -> Card does not match
* command 8 -> Vehicle number does not match
