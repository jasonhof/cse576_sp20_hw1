#include "image.h"

#include <iostream>

// HW0 #1
// const Image& im: input image
// int x,y: pixel coordinates
// int ch: channel of interest
// returns the 0-based location of the pixel value in the data array
int pixel_address(const Image& im, int x, int y, int ch)
  {
  /*
  // TODO: calculate and return the index
  // Find out the total size x and y
  int w = im.w; // width of image or total x
  int h = im.h; // height of image or total y
  int c = im.c; // channels of image
  int add = 0;  // address to return
  // Go over the address by x
  add = add + x;
  // Go over the address by y * x's
  add = add + (y * w);
  // Go over by ch whole images
  add = add + (ch * w * h);
  // NOT_IMPLEMENTED();
  //cout << "hi";
  //cout << w*h;
  //cout << "lo";
  //cout << add;
  int add2 = x + (y*im.w) + (ch*im.w*im.h);

  return add;
  */
  return (x + (y*im.w) + (ch*im.w*im.h));
  }

// HW0 #1
// const Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
// returns the value of the clamped pixel at channel ch
float get_clamped_pixel(const Image& im, int x, int y, int ch)
  {
  // TODO: clamp the coordinates and return the correct pixel value
  if (x<0) {x=0;}
  else if (x>=im.w) {x=im.w-1;}
  if (y<0) {y=0;}
  else if (y>=im.h) {y=im.h-1;}
  if (ch<0) {ch=0;}
  else if (ch>=im.c) {ch=im.c-1;}
  //NOT_IMPLEMENTED();

  return im(x,y,ch);
  }


// HW0 #1
// Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
void set_pixel(Image& im, int x, int y, int c, float value)
  {
  // im(x,y,c) = value;
  // TODO: Only set the pixel to the value if it's inside the image
  if (x<0 || x>=im.w || y<0 || y>=im.h || c<0 || c>=im.c)
  {
    cout << "Returned with args=" << x << " " << y << " " << c << endl;
    return;
  }
  im(x,y,c) = value;
  //NOT_IMPLEMENTED();

  }



// HW0 #2
// Copies an image
// Image& to: destination image
// const Image& from: source image
void copy_image(Image& to, const Image& from)
  {
  // allocating data for the new image
  to.data=(float*)calloc(from.w*from.h*from.c,sizeof(float));
  to.w=from.w;
  to.h=from.h;
  to.c=from.c;
  cout << "copy image readout" << endl;
  cout <<"to.w="<<to.w<<" from.w="<<from.w<<"to.h="<<to.h<<" from.h="<<from.h<<"to.c="<<to.c<<" from.c="<<from.c<<endl;
  cout<<"&to="<<&to<<" &from="<<&from<<endl;
  // memcpy method (not working)
  // memcpy(to.data, from.data, (sizeof(from)));

  // Loop method
  int ind = 0;
  for (int cn=0;cn<from.c;cn++)
  {
    for (int hn=0;hn<from.h;hn++)
    {
      for (int wn=0;wn<from.w;wn++)
      {
        ind = wn+ (hn*to.w) + (cn*to.w*to.h);
        to.data[ind] = from.data[ind];
        //to.data[wn,hn,cn] = from.data[wn,hn,cn];
        //cout<<"from.data[wn,hn,cn] of ["<<wn<<","<<hn<<","<<cn<<"]="<<from.data[wn,hn,cn]<<endl;
        //cout<<"to.data[wn,hn,cn] of ["<<wn<<","<<hn<<","<<cn<<"]="<<to.data[wn,hn,cn]<<endl;
      }
    }
  }

  // TODO: populate the remaining fields in 'to' and copy the data
  // You might want to check how 'memcpy' function works

  //NOT_IMPLEMENTED();

  }
