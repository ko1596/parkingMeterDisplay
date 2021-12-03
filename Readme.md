gst-launch-1.0 videotestsrc ! video/x-raw, width=1920, height=1080 ! autovideosink
gst-launch-1.0 videotestsrc pattern=10 ! video/x-raw, width=768, height=990 ! autovideosink         //顯示雪花螢幕