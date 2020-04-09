#include "../image.h"
#include "../utils.h"

#include <iostream>
#include <string>

using namespace std;

void test_jason1()
  {
  cout << "Running test_jason() ... "<< endl;
  Image im = load_image("data/dots.png");
  // Test within image
  cout << "im.w="<< im.w<<", im.h="<< im.h<< ", im.c=" << im.c << endl;
  cout << "im(0,1,1)="<<im(0,1,1)<<endl;
  cout << "im(1,0,1)="<<im(1,0,1)<<endl;
  cout << "im(3,1,0)="<<im(3,1,0)<<", im(3,1,1)="<<im(3,1,1)<<", im(3,1,2)="<<im(3,1,2)<< endl;
  cout << "for loop within test_jason()" << endl;
  for (int cn=0;cn<im.c;cn++)
  {
    for (int hn=0;hn<im.h;hn++)
    {
      for (int wn=0;wn<im.w;wn++)
      {
        cout << "im("<<wn<<","<<hn<<","<<cn<<")="<<im(wn,hn,cn)<<endl;
      }
    }
  }
  TEST(within_eps(0, im(0,0,0)));
  TEST(within_eps(1, im.clamped_pixel(1,0,1)));
  TEST(within_eps(0, im.clamped_pixel(2,0,1)));

  // Test padding
  TEST(within_eps(1, im.clamped_pixel(0,3,1)));
  TEST(within_eps(1, im.clamped_pixel(7,8,0)));
  TEST(within_eps(0, im.clamped_pixel(7,8,1)));
  TEST(within_eps(1, im.clamped_pixel(7,8,2)));
  }

void test_get_pixel()
  {
  Image im = load_image("data/dots.png");
  // Test within image
  TEST(within_eps(0, im.clamped_pixel(0,0,0)));
  TEST(within_eps(1, im.clamped_pixel(1,0,1)));
  TEST(within_eps(0, im.clamped_pixel(2,0,1)));

  // Test padding
  TEST(within_eps(1, im.clamped_pixel(0,3,1)));
  TEST(within_eps(1, im.clamped_pixel(7,8,0)));
  TEST(within_eps(0, im.clamped_pixel(7,8,1)));
  TEST(within_eps(1, im.clamped_pixel(7,8,2)));
  }

void test_set_pixel()
  {
  cout << "Running test_set_pixel() ... "<< endl;
  Image im = load_image("data/dots.png");
  Image d(4,2,3);

  d.set_pixel(0,0,0,0); d.set_pixel(0,0,1,0); d.set_pixel(0,0,2,0);
  d.set_pixel(1,0,0,1); d.set_pixel(1,0,1,1); d.set_pixel(1,0,2,1);
  d.set_pixel(2,0,0,1); d.set_pixel(2,0,1,0); d.set_pixel(2,0,2,0);
  d.set_pixel(3,0,0,1); d.set_pixel(3,0,1,1); d.set_pixel(3,0,2,0);
  // d.set_pixel(5,0,0,1); d.set_pixel(3,0,1,1); d.set_pixel(3,0,2,0);

  d.set_pixel(0,1,0,0); d.set_pixel(0,1,1,1); d.set_pixel(0,1,2,0);
  d.set_pixel(1,1,0,0); d.set_pixel(1,1,1,1); d.set_pixel(1,1,2,1);
  d.set_pixel(2,1,0,0); d.set_pixel(2,1,1,0); d.set_pixel(2,1,2,1);
  d.set_pixel(3,1,0,1); d.set_pixel(3,1,1,0); d.set_pixel(3,1,2,1);

  // Test images are same
  TEST(same_image(im, d));
  }

void test_grayscale()
  {
  Image im = load_image("data/colorbar.png");
  Image gray = rgb_to_grayscale(im);
  gray.save_image("output/gray_prod");
  Image g = load_image("data/gray.png");
  TEST(same_image(gray, g));
  }

void test_copy()
  {
  cout<<"Running test_copy ...";
  Image im = load_image("data/dog.jpg");
  Image c = im;
  cout<<"im.data[0,0,3]="<<im.data[0,0,3]<<endl;
  cout<<"c.data[0,0,3]="<<c.data[0,0,3]<<endl;
  TEST(same_image(im, c));
  im.save_image("output/dog_orig");
  c.save_image("output/dog_copy");
  }

void test_shift()
  {
  Image im = load_image("data/dog.jpg");
  Image c = im;
  shift_image(c, 1, .1);
  TEST(within_eps(im.data[0], c.data[0]));
  TEST(within_eps(im.data[im.w*im.h+13] + .1,  c.data[im.w*im.h + 13]));
  TEST(within_eps(im.data[2*im.w*im.h+72],  c.data[2*im.w*im.h + 72]));
  TEST(within_eps(im.data[im.w*im.h+47] + .1,  c.data[im.w*im.h + 47]));
  }

// Jason wrote this function to test clamp_image function
void test_shift2()
  {
  cout << "Running test_shift2 and saving images ..." <<endl;
  Image im = load_image("data/dog.jpg");
  Image c = im;
  shift_image(c, 0, .4);
  shift_image(c, 1, .4);
  shift_image(c, 2, .4);
  //TEST(within_eps(im.data[0], c.data[0]));
  //TEST(within_eps(im.data[im.w*im.h+13] + .1,  c.data[im.w*im.h + 13]));
  //TEST(within_eps(im.data[2*im.w*im.h+72],  c.data[2*im.w*im.h + 72]));
  //TEST(within_eps(im.data[im.w*im.h+47] + .1,  c.data[im.w*im.h + 47]));
  c.save_image("output/preclampdog");
  clamp_image(c);
  c.save_image("output/postclampdog");
  }


void test_rgb_to_hsv()
  {
  Image im = load_image("data/dog.jpg");
  rgb_to_hsv(im);
  Image hsv = load_image("data/dog.hsv.png");
  TEST(same_image(im, hsv));
  }

void test_hsv_to_rgb()
  {
  Image im = load_image("data/dog.jpg");
  Image c = im;
  rgb_to_hsv(im);
  save_image(im,"output/midhsv");
  hsv_to_rgb(im);
  save_image(im,"output/endrgb");
  TEST(same_image(im, c));
  }

// Jason added from assignment page
void test_hsv_to_rgb2()
  {
  // 6-7. Colorspace and saturation
  Image im2 = load_image("data/dog.jpg");
  rgb_to_hsv(im2);
  shift_image(im2, 1, .2);
  clamp_image(im2);
  hsv_to_rgb(im2);
  im2.save_image("output/colorspace_result");
  }

// Jason added from assignment page
void test_hsv_to_rgb3()
  {
  // 6-7. Colorspace and saturation
  Image im2 = load_image("data/dog.jpg");
  rgb_to_hsv(im2);
  scale_image(im2, 1, .2);
  clamp_image(im2);
  hsv_to_rgb(im2);
  im2.save_image("output/dog_scale_saturated");
  }

void test_rgb2lch2rgb()
  {
  Image im = load_image("data/dog.jpg");
  Image c = im;

  rgb_to_lch(im);
  im.save_image("output/lch2005");
  lch_to_rgb(im);
  TEST(same_image(im, c));
  }

void test_dog()
  {
    Image im2 = load_image("data/dog.jpg");
    for (int i=0; i<im2.w; i++)
      for (int j=0; j<im2.h; j++)
        im2(i,j,0) = 0;
    im2.save_image("output/set_pixel_result");
  }


void run_tests()
  {
  /*
  test_get_pixel();
  test_set_pixel();
  test_copy();
  test_shift();
  test_grayscale();
  test_rgb_to_hsv();
  test_hsv_to_rgb();
  test_rgb2lch2rgb();
  test_rgb2lch2rgb();

  test_hsv_to_rgb2();
  test_hsv_to_rgb3();
  test_hsv_to_rgb();
  test_rgb_to_hsv();
  test_shift2();
  test_shift();
  test_grayscale();
  test_copy();
  test_set_pixel();
  test_jason1();
  */
  test_grayscale();
  test_jason1();
  test_get_pixel();
  printf("%d tests, %d passed, %d failed\n", tests_total, tests_total-tests_fail, tests_fail);
  }

int main(int argc, char **argv)
  {
  // Image manipulation for fun testing.

  Image im2 = load_image("data/dog.jpg");
  for (int i=0; i<im2.w; i++)
      for (int j=0; j<im2.h; j++)
          im2(i, j, 0) = 0;
  im2.save_image("output/pixel_modifying_output");

  // Running example tests
  test_dog();
  run_tests();

  return 0;
  }
