// Copyright (C) 2015 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES
#define KS 3 //KERNELSIZE
#include "median_module.h"

void median_module::do_median() {

    //100 x 100 Image and 3x3 window
    unsigned char window[KS*3];
    unsigned char output[width][height];
    unsigned int temp;
    char in;


    for (unsigned int w=0; w <= width-1; w++){
        for (unsigned int h=0; h <= height-1; h++){
            if (w ==0 && h ==0){
                //fill border pixels with first pixel
                temp = read_pixel(w,h);
                window[8] = read_pixel(w+1,h+1);
                window[7] = read_pixel(w,h+1);
                window[6] = window[7];
                window[5] = read_pixel(w+1,h);
                window[4] = temp;
                window[3] = temp;
                window[2] = window[5];
                window[1] = temp;
                window[0] = temp;
                //printf("corner upper left:\n\r");
                //scanf("%c",&in);

            }
            else if (w == width-1 && h == height-1 ){
                temp = read_pixel(w,h);
                window[0] = read_pixel(w-1,h-1);
                window[1] = read_pixel(w,h-1);
                window[2] = window[1];
                window[3] = read_pixel(w-1,h);
                window[4] = temp;
                window[5] = temp;
                window[6] = window[3];
                window[7] = temp;
                window[8] = temp;
                //printf("corner lower right \n\r");
                //scanf("%c",&in);
            }
            else if (w == width-1 && h ==0){
                temp = read_pixel(w,h);
                window[8] = read_pixel(w,h+1);
                window[7] = window[8];
                window[6] = read_pixel(w-1,h+1);
                window[5] = temp;
                window[4] = temp;
                window[3] = read_pixel(w-1,h);
                window[2] = read_pixel(w-1,h);
                window[1] = temp;
                window[0] = window[2];
                //printf("corner upper right:\n\r");
                //scanf("%c",&in);
            }
            else if (w == 0 && h == height-1 ){
                temp = read_pixel(w,h);
                window[0] = read_pixel(w,h-1);
                window[1] = window[0];
                window[2] = read_pixel(w+1,h-1);
                window[3] = temp;
                window[4] = temp;
                window[5] = read_pixel(w+1,h);
                window[6] = temp;
                window[7] = temp;
                window[8] = window[5];
                //printf("corner lower left:\n\r");
                //scanf("%c",&in);
            }
            else if (w == 0 && h > 0 && h < height-1){
                window[0] = read_pixel(w,h-1);
                window[1] = window[0];
                window[2] = read_pixel(w+1,h-1);
                window[3] = read_pixel(w,h);
                window[4] = window[3];
                window[5] = read_pixel(w+1,h);
                window[6] = read_pixel(w,h+1);
                window[7] = window[6];
                window[8] = read_pixel(w+1,h+1);
            }
            else if (w > 0 && w < width-1 && h == 0){
                window[0] = read_pixel(w-1,h);
                window[1] = read_pixel(w,h);
                window[2] = read_pixel(w+1,h);
                window[3] = window[0];
                window[4] = window[1];
                window[5] = window[2];
                window[6] = read_pixel(w-1,h+1);
                window[7] = read_pixel(w,h+1);
                window[8] = read_pixel(w+1,h+1);
            }

            else{
                for (unsigned int i=0; i <= KS-1;i++){
                    window[(i+0)+i*(KS-1)]= read_pixel(w-1,h+i-1);//w+1-1,h+1+i-1);
                    window[(i+1)+i*(KS-1)] = read_pixel(w,h+i-1);//w+1,h+1+i-1);
                    window[(i+2)+i*(KS-1)] = read_pixel(w+1,h+i-1);//w+1+1,h+1+i-1);
                    //printf("Value:\n %x\n\r %x\n\r %x\n\r",window[3*i],window[3*i+1],window[3*i+2]);
                }
            }



               //***Insertion sort algorithm***//
               unsigned int tmp;
               int m , k;
               for(m = 1; m < 9; m++){
                   tmp = window[m];
                   for(k = m-1; (k >= 0) && (window[k]<tmp); k--){
                       window[k+1] = window[k];
                   }
                   window[k+1] = tmp;
               }

               //***Writing output image***//
               output[w][h] = window[KS+1];
               //if (w == 0 && h == 0){
               //printf("values first pixel: %x \n\r",window[KS+1]);
               //}
               //wait();
        }
        //if (w == width - 3){
        //printf("GO on last here: type!\n\r");
        //scanf("%c",&in);}
    }

    for (unsigned int w=0; w <= width-1; w++)
    {
        for (unsigned int h=0; h <= height-1; h++)
        {
            write_pixel(output[w][h],w,h);
        }
    }
    finish.write(true);
    wait();
}



//    for (unsigned int w=0; w <= width-1; w++){
//        for (unsigned int h=0; h <= height-1; h++){
//            //printf("%d. round: \n\r",h);
//            if (w > 0 && h > 0 && w < width-1 && h < height-1){
//                for (int i=0; i <= KS-1;i++){
//                    window[(i+0)+i*(KS-1)]= read_pixel(w-1,h+i-1);//w+1-1,h+1+i-1);
//                    window[(i+1)+i*(KS-1)] = read_pixel(w,h+i-1);//w+1,h+1+i-1);
//                    window[(i+2)+i*(KS-1)] = read_pixel(w+1,h+i-1);//w+1+1,h+1+i-1);
//                    //printf("Value:\n %x\n\r %x\n\r %x\n\r",window[3*i],window[3*i+1],window[3*i+2]);
//                }

//               //***Insertion sort algorithm***//
//               unsigned int temp;
//               int m , k;
//               for(m = 1; m < 9; m++){
//                   temp = window[m];
//                   for(k = m-1; (k >= 0) && (window[k]<temp); k--){
//                       window[k+1] = window[k];
//                   }
//                   window[k+1] = temp;
//               }

//               //***Writing output image***//
//               if (h == 0 || w == 0 || w == width-1 || h == height-1 ){
//                    output[w][h] = 0x00;
//               }
//               else{
//                    output[w][h] = window[4]; //middle of sorted window as median
//               }
//            }
//        }
//    }
//    for (unsigned int w=0; w <= width-1; w++)
//    {
//        for (unsigned int h=0; h <= height-1; h++)
//        {
//            write_pixel(output[w][h],w,h);
//        }
//    }
//    finish.write(true);
//    wait();
//}


//void median_module::do_median()
//{
//  unsigned char filtered_img[width][height];

//  for(int i = 1; i < width-1; i++){
//    for(unsigned int j = 1; j < height-1; j++){
//      if(j == 1){
//        temp[0] = read_pixel(i-1,j-1);
//        temp[1] = read_pixel(i-1,j);
//        temp[2] = read_pixel(i-1,j+1);
//        temp[3] = read_pixel(i,j-1);
//        temp[4] = read_pixel(i,j);
//        temp[5] = read_pixel(i,j+1);
//        temp[6] = read_pixel(i+1,j-1);
//        temp[7] = read_pixel(i+1,j);
//        temp[8] = read_pixel(i+1,j+1);
//      }
//      else{
//        temp[0] = temp[1];
//        temp[1] = temp[2];
//        temp[2] = read_pixel(i-1,j+1);
//        temp[3] = temp[4];
//        temp[4] = temp[5];
//        temp[5] = read_pixel(i,j+1);
//        temp[6] = temp[7];
//        temp[7] = temp[8];
//        temp[8] = read_pixel(i+1,j+1);
//      }
//      wait();

//      std::copy(temp, temp+9, temp_sort);

//      int index;
//      unsigned char val;

//      for(int k = 0; k < 5; k++){
//        index = k;
//        for(int l = k+1; l < 9; l++){
//          if(temp_sort[l] < temp_sort[index])
//            index = l;
//        }
//        val = temp_sort[k];
//        temp_sort[k] = temp_sort[index];
//        temp_sort[index] = val;
//      }
//      filtered_img[i][j] = temp_sort[4];
//      wait();
//    }
//  }
//  for(int i = 1; i < width-1; i++){
//    for(int j = 1; j < height-1; j++){
//      write_pixel(filtered_img[i][j], i, j);
//    }
//  }
//  finish.write(true);
//  wait();
//}

unsigned int median_module::read_pixel(int x, int y){
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);

  unsigned char data = 255;
  trans->set_command(tlm::TLM_READ_COMMAND);
  trans->set_address(x*(width-1)+y);//x*width+y
  trans->set_data_ptr(&data);
  trans->set_data_length(1);
  trans->set_streaming_width(1);
  trans->set_byte_enable_ptr(0);
  trans->set_dmi_allowed(false);
  trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

  socket->b_transport(*trans, delay);

  //cout << "data read from address: " << x << ", " << y << " is " << int(data) << "\n";

  wait(delay);

  return data;
}

void median_module::write_pixel(unsigned char val, unsigned int x, unsigned int y){
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);

  trans->set_command(tlm::TLM_WRITE_COMMAND);
  trans->set_address(x*(width-1)+y); //width
  trans->set_data_ptr(&val);
  trans->set_data_length(1);
  trans->set_streaming_width(1);
  trans->set_byte_enable_ptr(0);
  trans->set_dmi_allowed(false);
  trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

  //cout << "data written to address: " << x << ", " << y << " is " << int(val) << "\n";

  socket->b_transport(*trans, delay);

  wait(delay);
}
