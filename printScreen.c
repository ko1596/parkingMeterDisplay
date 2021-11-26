// #include <unistd.h>
// #include <stdio.h>
// #include <fcntl.h>
// #include <linux/fb.h>
// #include <sys/mman.h>


// int main () {
//  int fp=0;
//  struct fb_var_screeninfo vinfo;
//  struct fb_fix_screeninfo finfo;
//  fp = open ("/dev/fb0",O_RDWR);


//  if (fp < 0){
//   printf("Error : Can not open framebuffer device/n");
//   exit(1);
//  }


//  if (ioctl(fp,FBIOGET_FSCREENINFO,&finfo)){
//   printf("Error reading fixed information/n");
//   exit(2);
//  }
 
//  if (ioctl(fp,FBIOGET_VSCREENINFO,&vinfo)){
//   printf("Error reading variable information/n");
//   exit(3);
//  }


//  printf("The mem is :%d\n",finfo.smem_len);
//  printf("The line_length is :%d\n",finfo.line_length);
//  printf("The xres is :%d\n",vinfo.xres);
//  printf("The yres is :%d\n",vinfo.yres);
//  printf("bits_per_pixel is :%d\n",vinfo.bits_per_pixel);
//  close (fp);
// }

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>


int main () {
 int fp=0;
 struct fb_var_screeninfo vinfo;
 struct fb_fix_screeninfo finfo;
 long screensize=0;
 char *fbp = 0;
 int x = 0, y = 0;
 long location = 0;
 fp = open ("/dev/fb0",O_RDWR);


 if (fp < 0){
  printf("Error : Can not open framebuffer device/n");
  exit(1);
 }


 if (ioctl(fp,FBIOGET_FSCREENINFO,&finfo)){
  printf("Error reading fixed information/n");
  exit(2);
 }
 
 if (ioctl(fp,FBIOGET_VSCREENINFO,&vinfo)){
  printf("Error reading variable information/n");
  exit(3);
 }


  screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
 /*這就是把fp所指的檔案中從開始到screensize大小的內容給映射出來，得到一個指向這塊空間的指標*/
 fbp =(char *) mmap (0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fp,0);
   if ((int) fbp == -1)
     {
        printf ("Error: failed to map framebuffer device to memory./n");
        exit (4);
     }
/*這是你想畫的點的位置座標,(0，0)點在螢幕左上角*/
  x = 100;
  y = 100;
  location = x * (vinfo.bits_per_pixel / 8) + y  *  finfo.line_length;


  *(fbp + location) = 100;  /* 藍色的色深 */  /*直接賦值來改變螢幕上某點的顏色*/
  *(fbp + location + 1) = 15; /* 綠色的色深*/   
  *(fbp + location + 2) = 200; /* 紅色的色深*/   
  *(fbp + location + 3) = 0;  /* 是否透明*/  
  munmap (fbp, screensize); /*解除對映*/
  close (fp);    /*關閉檔案*/
  return 0;


}