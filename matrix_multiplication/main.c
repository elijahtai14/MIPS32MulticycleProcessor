
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

float * generate_rand_input(int rows, int cols) {
  // ============================================
  // Allocating the matrices based on dimensions rows x cols
  // ============================================
  float * mat = malloc( rows * cols * sizeof(float));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      mat[i * cols + j] = rand() % 16;
    }
  }

  return mat;
}

int16_t * generate_rand_input_int16(int rows, int cols) {
  // ============================================
  // Allocating the matrices based on dimensions rows x cols
  // ============================================
  int16_t * mat = malloc( rows * cols * sizeof(int16_t));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      mat[i * cols + j] = rand() % 16;
    }
  }

  return mat;
}

int8_t * generate_rand_input_int8(int rows, int cols) {
  // ============================================
  // Allocating the matrices based on dimensions rows x cols
  // ============================================
  int8_t * mat = malloc( rows * cols * sizeof(int8_t));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      mat[i * cols + j] = rand() % 16;
    }
  }

  return mat;
}

float * generate_output(int rows, int cols) {
  // ============================================
  // Allocating the output matrix based on dimensions rows x cols
  // with 0's as initial value
  // ============================================
  float * mat = malloc( rows * cols * sizeof(float));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      mat[i * cols + j] = 0.0;
    }
  }

  return mat;
}

int16_t * generate_output_int16(int rows, int cols) {
  // ============================================
  // Allocating the output matrix based on dimensions rows x cols
  // with 0's as initial value
  // ============================================
  int16_t * mat = malloc( rows * cols * sizeof(int16_t));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      mat[i * cols + j] = 0.0;
    }
  }

  return mat;
}

int8_t * generate_output_int8(int rows, int cols) {
  // ============================================
  // Allocating the output matrix based on dimensions rows x cols
  // with 0's as initial value
  // ============================================
  int8_t * mat = malloc( rows * cols * sizeof(int8_t));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      mat[i * cols + j] = 0.0;
    }
  }

  return mat;
}


void print_mat(float * mat, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%f ", mat[i * cols + j]);
    }
    printf("\n");
  }
}



// ============================================
// Comparing two matrices of the same size for correctness
// ============================================
bool compare_matrices(float * mat1, float * mat2, int rows, int cols) {
  bool equal = true;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int index = i * cols + j;
      bool check = (mat1[index] == mat2[index]);
      equal = equal & check;
    }
  }
  return equal;
}

bool compare_matrices_int16(int16_t * mat1, int16_t * mat2, int rows, int cols) {
  bool equal = true;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int index = i * cols + j;
      bool check = (mat1[index] == mat2[index]);
      equal = equal & check;
    }
  }
  return equal;
}

bool compare_matrices_int8(int8_t * mat1, int8_t * mat2, int rows, int cols) {
  bool equal = true;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int index = i * cols + j;
      bool check = (mat1[index] == mat2[index]);
      equal = equal & check;
    }
  }
  return equal;
}



// ============================================
// Implementation of naive matrix multiplication
// a = b * c
// a: matrix of dimension out_rows x out_cols
// b: matrix of dimension out_rows x in_cols
// c: matrix of dimension in_cols x out_cols
// ============================================
void naivemm(float * a, float * b, float * c, int out_rows, int out_cols, int in_cols, int offsetA, int offsetB, int offsetC) {
  for (int i = 0; i < out_rows; i++) {
    for (int j = 0; j < out_cols; j++) {
      int a_index = i * (out_cols + offsetA) + j;
      for (int k = 0; k < in_cols; k++) {
        int b_index = i * (in_cols  + offsetB) + k;
        int c_index = k * (out_cols + offsetC) + j;
        a[a_index] = a[a_index] + (b[b_index] * c[c_index]);
      }
    }
  }
}

void naivemm_int16(int16_t * a, int16_t * b, int16_t * c, int out_rows, int out_cols, int in_cols, int offsetA, int offsetB, int offsetC) {
  for (int i = 0; i < out_rows; i++) {
    for (int j = 0; j < out_cols; j++) {
      int a_index = i * (out_cols + offsetA) + j;
      for (int k = 0; k < in_cols; k++) {
        int b_index = i * (in_cols  + offsetB) + k;
        int c_index = k * (out_cols + offsetC) + j;
        a[a_index] = a[a_index] + (b[b_index] * c[c_index]);
      }
    }
  }
}

void naivemm_int8(int8_t * a, int8_t * b, int8_t * c, int out_rows, int out_cols, int in_cols, int offsetA, int offsetB, int offsetC) {
  for (int i = 0; i < out_rows; i++) {
    for (int j = 0; j < out_cols; j++) {
      int a_index = i * (out_cols + offsetA) + j;
      for (int k = 0; k < in_cols; k++) {
        int b_index = i * (in_cols  + offsetB) + k;
        int c_index = k * (out_cols + offsetC) + j;
        a[a_index] = a[a_index] + (b[b_index] * c[c_index]);
      }
    }
  }
}

void tiledmm(float * a, float * b, float * c, int out_rows, int out_cols, int in_cols, int tile_size) {

  int num_tiles_vert_B = out_rows / tile_size;
  int rem_vert_B = out_rows % tile_size;

  int num_tiles_acro_B = in_cols / tile_size;
  int rem_acro_B = in_cols % tile_size;

  int num_tiles_acro_C = out_cols / tile_size;
  int rem_acro_C = out_cols % tile_size;

  float* tile_mat_b;
  float* tile_mat_c;
  float* tile_mat_a;

  int offset_B = in_cols  - tile_size;
  int offset_C = out_cols - tile_size;
  int offset_A = out_cols - tile_size;

  // Just for speed
  int tile_size_x_in_cols = tile_size * in_cols;
  int tile_size_x_out_cols = tile_size * out_cols;

  // Deal with square tiles
  for (int row_B = 0; row_B < num_tiles_vert_B; row_B++){
    for (int col_C = 0; col_C < num_tiles_acro_C; col_C++){
      for (int tile = 0; tile < num_tiles_acro_B; tile++){

        tile_mat_b = &b[row_B * tile_size_x_in_cols + tile * tile_size];
        tile_mat_c = &c[tile * tile_size_x_out_cols + col_C * tile_size];
        tile_mat_a = &a[row_B * tile_size_x_out_cols  + col_C * tile_size];

        naivemm(tile_mat_a, tile_mat_b, tile_mat_c, tile_size, tile_size, tile_size, offset_A, offset_B, offset_C);
      }
    }
  }

  // Deal with remainders: 1) Fixing the center
  int rem_out_rows;
  int rem_out_cols;
  int rem_in_cols;

  if (rem_acro_B > 0){
     tile_mat_b = &b[num_tiles_acro_B * tile_size];
     tile_mat_c = &c[out_cols * num_tiles_acro_B * tile_size];
     tile_mat_a = a;

     rem_out_rows = num_tiles_vert_B * tile_size;
     rem_out_cols = num_tiles_acro_C * tile_size;
     rem_in_cols = rem_acro_B;

     offset_B = in_cols - rem_in_cols;
     offset_C = out_cols - rem_out_cols;
     offset_A = out_cols - rem_out_cols;

     naivemm(tile_mat_a, tile_mat_b, tile_mat_c, rem_out_rows, rem_out_cols, rem_in_cols, offset_A, offset_B, offset_C);

     //2) Fixing the bottom
     tile_mat_b = &b[num_tiles_vert_B * tile_size_x_in_cols];
     tile_mat_c = c;
     tile_mat_a = &a[num_tiles_vert_B * tile_size_x_out_cols];

     rem_out_rows = rem_vert_B;
     // rem_out_cols = num_tiles_acro_C * tile_size;
     rem_in_cols = in_cols;

     offset_B = 0;
     // offset_C = out_cols - rem_out_cols;
     // offset_A = out_cols - rem_out_cols;

     naivemm(tile_mat_a, tile_mat_b, tile_mat_c, rem_out_rows, rem_out_cols, rem_in_cols, offset_A, offset_B, offset_C);
  }

  //3) Fixing the right side
  if (rem_acro_C > 0){
   tile_mat_b = b;
   tile_mat_c = &c[num_tiles_acro_C * tile_size];
   tile_mat_a = &a[num_tiles_acro_C * tile_size];

   rem_out_rows = num_tiles_vert_B * tile_size;
   rem_out_cols = rem_acro_C;
   rem_in_cols = in_cols;

   offset_B = 0;
   offset_C = out_cols - rem_out_cols;
   offset_A = out_cols - rem_acro_C;

   naivemm(tile_mat_a, tile_mat_b, tile_mat_c, rem_out_rows, rem_out_cols, rem_in_cols, offset_A, offset_B, offset_C);
  }
  //4) Fixing the corner
  if (rem_acro_C > 0 && rem_acro_B > 0){
     tile_mat_b = &b[in_cols * num_tiles_vert_B * tile_size];
     tile_mat_c = &c[num_tiles_acro_C * tile_size];
     tile_mat_a = &a[out_cols * num_tiles_vert_B * tile_size + num_tiles_acro_C * tile_size];

     rem_out_rows = rem_vert_B;
     rem_out_cols = rem_acro_C;
     rem_in_cols = in_cols;

     //offset_B = 0;
     //offset_C = out_cols - rem_out_cols;
     //offset_A = out_cols - rem_acro_C;

     naivemm(tile_mat_a, tile_mat_b, tile_mat_c, rem_out_rows, rem_out_cols, rem_in_cols, offset_A, offset_B, offset_C);
  }
}

void tiledmm_int16(int16_t * a, int16_t * b, int16_t * c, int out_rows, int out_cols, int in_cols, int tile_size) {

  int num_tiles_vert_B = out_rows / tile_size;
  int rem_vert_B = out_rows % tile_size;

  int num_tiles_acro_B = in_cols / tile_size;
  int rem_acro_B = in_cols % tile_size;

  int num_tiles_acro_C = out_cols / tile_size;
  int rem_acro_C = out_cols % tile_size;

  int16_t* tile_mat_b;
  int16_t* tile_mat_c;
  int16_t* tile_mat_a;

  int offset_B = in_cols  - tile_size;
  int offset_C = out_cols - tile_size;
  int offset_A = out_cols - tile_size;

  // Just for speed
  int tile_size_x_in_cols = tile_size * in_cols;
  int tile_size_x_out_cols = tile_size * out_cols;

  // Deal with square tiles
  for (int row_B = 0; row_B < num_tiles_vert_B; row_B++){
    for (int col_C = 0; col_C < num_tiles_acro_C; col_C++){
      for (int tile = 0; tile < num_tiles_acro_B; tile++){

        tile_mat_b = &b[row_B * tile_size_x_in_cols + tile * tile_size];
        tile_mat_c = &c[tile * tile_size_x_out_cols + col_C * tile_size];
        tile_mat_a = &a[row_B * tile_size_x_out_cols  + col_C * tile_size];

        naivemm_int16(tile_mat_a, tile_mat_b, tile_mat_c, tile_size, tile_size, tile_size, offset_A, offset_B, offset_C);
      }
    }
  }

  // Deal with remainders: 1) Fixing the center
  int rem_out_rows;
  int rem_out_cols;
  int rem_in_cols;

  if (rem_acro_B > 0){
     tile_mat_b = &b[num_tiles_acro_B * tile_size];
     tile_mat_c = &c[out_cols * num_tiles_acro_B * tile_size];
     tile_mat_a = a;

     rem_out_rows = num_tiles_vert_B * tile_size;
     rem_out_cols = num_tiles_acro_C * tile_size;
     rem_in_cols = rem_acro_B;

     offset_B = in_cols - rem_in_cols;
     offset_C = out_cols - rem_out_cols;
     offset_A = out_cols - rem_out_cols;

     naivemm_int16(tile_mat_a, tile_mat_b, tile_mat_c, rem_out_rows, rem_out_cols, rem_in_cols, offset_A, offset_B, offset_C);

     //2) Fixing the bottom
     tile_mat_b = &b[num_tiles_vert_B * tile_size_x_in_cols];
     tile_mat_c = c;
     tile_mat_a = &a[num_tiles_vert_B * tile_size_x_out_cols];

     rem_out_rows = rem_vert_B;
     // rem_out_cols = num_tiles_acro_C * tile_size;
     rem_in_cols = in_cols;

     offset_B = 0;
     // offset_C = out_cols - rem_out_cols;
     // offset_A = out_cols - rem_out_cols;

     naivemm_int16(tile_mat_a, tile_mat_b, tile_mat_c, rem_out_rows, rem_out_cols, rem_in_cols, offset_A, offset_B, offset_C);
  }

  //3) Fixing the right side
  if (rem_acro_C > 0){
   tile_mat_b = b;
   tile_mat_c = &c[num_tiles_acro_C * tile_size];
   tile_mat_a = &a[num_tiles_acro_C * tile_size];

   rem_out_rows = num_tiles_vert_B * tile_size;
   rem_out_cols = rem_acro_C;
   rem_in_cols = in_cols;

   offset_B = 0;
   offset_C = out_cols - rem_out_cols;
   offset_A = out_cols - rem_acro_C;

   naivemm_int16(tile_mat_a, tile_mat_b, tile_mat_c, rem_out_rows, rem_out_cols, rem_in_cols, offset_A, offset_B, offset_C);
  }
  //4) Fixing the corner
  if (rem_acro_C > 0 && rem_acro_B > 0){
     tile_mat_b = &b[in_cols * num_tiles_vert_B * tile_size];
     tile_mat_c = &c[num_tiles_acro_C * tile_size];
     tile_mat_a = &a[out_cols * num_tiles_vert_B * tile_size + num_tiles_acro_C * tile_size];

     rem_out_rows = rem_vert_B;
     rem_out_cols = rem_acro_C;
     rem_in_cols = in_cols;

     //offset_B = 0;
     //offset_C = out_cols - rem_out_cols;
     //offset_A = out_cols - rem_acro_C;

     naivemm_int16(tile_mat_a, tile_mat_b, tile_mat_c, rem_out_rows, rem_out_cols, rem_in_cols, offset_A, offset_B, offset_C);
  }
}

void tiledmm_int8(int8_t * a, int8_t * b, int8_t * c, int out_rows, int out_cols, int in_cols, int tile_size) {

  int num_tiles_vert_B = out_rows / tile_size;
  int rem_vert_B = out_rows % tile_size;

  int num_tiles_acro_B = in_cols / tile_size;
  int rem_acro_B = in_cols % tile_size;

  int num_tiles_acro_C = out_cols / tile_size;
  int rem_acro_C = out_cols % tile_size;

  int8_t* tile_mat_b;
  int8_t* tile_mat_c;
  int8_t* tile_mat_a;

  int offset_B = in_cols  - tile_size;
  int offset_C = out_cols - tile_size;
  int offset_A = out_cols - tile_size;

  // Just for speed
  int tile_size_x_in_cols = tile_size * in_cols;
  int tile_size_x_out_cols = tile_size * out_cols;

  // Deal with square tiles
  for (int row_B = 0; row_B < num_tiles_vert_B; row_B++){
    for (int col_C = 0; col_C < num_tiles_acro_C; col_C++){
      for (int tile = 0; tile < num_tiles_acro_B; tile++){

        tile_mat_b = &b[row_B * tile_size_x_in_cols + tile * tile_size];
        tile_mat_c = &c[tile * tile_size_x_out_cols + col_C * tile_size];
        tile_mat_a = &a[row_B * tile_size_x_out_cols  + col_C * tile_size];

        naivemm_int8(tile_mat_a, tile_mat_b, tile_mat_c, tile_size, tile_size, tile_size, offset_A, offset_B, offset_C);
      }
    }
  }

  // Deal with remainders: 1) Fixing the center
  int rem_out_rows;
  int rem_out_cols;
  int rem_in_cols;

  if (rem_acro_B > 0){
     tile_mat_b = &b[num_tiles_acro_B * tile_size];
     tile_mat_c = &c[out_cols * num_tiles_acro_B * tile_size];
     tile_mat_a = a;

     rem_out_rows = num_tiles_vert_B * tile_size;
     rem_out_cols = num_tiles_acro_C * tile_size;
     rem_in_cols = rem_acro_B;

     offset_B = in_cols - rem_in_cols;
     offset_C = out_cols - rem_out_cols;
     offset_A = out_cols - rem_out_cols;

     naivemm_int8(tile_mat_a, tile_mat_b, tile_mat_c, rem_out_rows, rem_out_cols, rem_in_cols, offset_A, offset_B, offset_C);

     //2) Fixing the bottom
     tile_mat_b = &b[num_tiles_vert_B * tile_size_x_in_cols];
     tile_mat_c = c;
     tile_mat_a = &a[num_tiles_vert_B * tile_size_x_out_cols];

     rem_out_rows = rem_vert_B;
     // rem_out_cols = num_tiles_acro_C * tile_size;
     rem_in_cols = in_cols;

     offset_B = 0;
     // offset_C = out_cols - rem_out_cols;
     // offset_A = out_cols - rem_out_cols;

     naivemm_int8(tile_mat_a, tile_mat_b, tile_mat_c, rem_out_rows, rem_out_cols, rem_in_cols, offset_A, offset_B, offset_C);
  }

  //3) Fixing the right side
  if (rem_acro_C > 0){
   tile_mat_b = b;
   tile_mat_c = &c[num_tiles_acro_C * tile_size];
   tile_mat_a = &a[num_tiles_acro_C * tile_size];

   rem_out_rows = num_tiles_vert_B * tile_size;
   rem_out_cols = rem_acro_C;
   rem_in_cols = in_cols;

   offset_B = 0;
   offset_C = out_cols - rem_out_cols;
   offset_A = out_cols - rem_acro_C;

   naivemm_int8(tile_mat_a, tile_mat_b, tile_mat_c, rem_out_rows, rem_out_cols, rem_in_cols, offset_A, offset_B, offset_C);
  }
  //4) Fixing the corner
  if (rem_acro_C > 0 && rem_acro_B > 0){
     tile_mat_b = &b[in_cols * num_tiles_vert_B * tile_size];
     tile_mat_c = &c[num_tiles_acro_C * tile_size];
     tile_mat_a = &a[out_cols * num_tiles_vert_B * tile_size + num_tiles_acro_C * tile_size];

     rem_out_rows = rem_vert_B;
     rem_out_cols = rem_acro_C;
     rem_in_cols = in_cols;

     //offset_B = 0;
     //offset_C = out_cols - rem_out_cols;
     //offset_A = out_cols - rem_acro_C;

     naivemm_int8(tile_mat_a, tile_mat_b, tile_mat_c, rem_out_rows, rem_out_cols, rem_in_cols, offset_A, offset_B, offset_C);
  }
}

void test_matrix_sizes(){
  int NUMTESTS = 7;
  int TILESIZES[7] = {0, 8, 64, 128, 256, 512, 1204};

  int MATRIX_ROWS_B = 8;
  int MATRIX_COLS_B = 8; // for a non-square matrix

  int MATRIX_ROWS_C = MATRIX_COLS_B;
  int MATRIX_COLS_C = 8; // for a non-square matrix


  clock_t start_clocks[NUMTESTS];
  clock_t end_clocks[NUMTESTS];
  double cpu_time;

  int number_of_iterations = 16384; // TODO: Set this for consistent results

  float* mats_a[NUMTESTS];
  for (int i = 0; i < NUMTESTS; i++){
    mats_a[i] = generate_output(MATRIX_ROWS_B, MATRIX_COLS_C);
  }

  float * mat_b = generate_rand_input(MATRIX_ROWS_B, MATRIX_COLS_B);
  float * mat_c = generate_rand_input(MATRIX_ROWS_C, MATRIX_COLS_C);


  // ============================================
  // Running and profiling (I decided not to generate a new radom matrix per iteration)
  // ============================================


  start_clocks[0] = clock();
  for (int iter = 0; iter < number_of_iterations; iter++) {
    naivemm(mats_a[0],  mat_b, mat_c, MATRIX_ROWS_B, MATRIX_COLS_C, MATRIX_COLS_B, 0, 0, 0);
  }
  end_clocks[0] = clock();

  for (int i = 1; i < NUMTESTS; i++){
    start_clocks[i] = clock();
    for (int iter = 0; iter < number_of_iterations; iter++) {
      tiledmm(mats_a[i],  mat_b, mat_c, MATRIX_ROWS_B, MATRIX_COLS_C, MATRIX_COLS_B, TILESIZES[i]);
    }
    end_clocks[i] = clock();
  }

  // Print final output matrix for debugging purposes. Can comment out if not
  // needed.

  //print_mat(mat_a, MATRIX_ROWS_B, MATRIX_COLS_C);
  //print_mat(mat_a2, MATRIX_ROWS_B, MATRIX_COLS_C);

  // Verify that optimized tiled implementation is
  // also correct.

  for (int i = 1; i < NUMTESTS; i++){
    if ( compare_matrices(mats_a[0], mats_a[i], MATRIX_ROWS_B, MATRIX_COLS_C) ) {
      printf("Matrix multiplication is functionally correct.\n");
    } else {
      printf("[Error] Matrix multiplication is not functionally correct...\n");
    }
  }

  // Compute execution time.
  printf("Naive: \n");
  printf("=========================================\n");
  cpu_time = ( (double) (end_clocks[0] - start_clocks[0]) ) / CLOCKS_PER_SEC;
  printf("Total execution time: \t\t %lf seconds \n", cpu_time);
  cpu_time = cpu_time / (double) number_of_iterations; // time per iteration
  printf("Per iteration execution time: \t %lf seconds \n", cpu_time);
  printf("=========================================\n");


  for (int i = 1; i < NUMTESTS; i++) {
  printf("Tile Size: %d \n", TILESIZES[i]);
  printf("=========================================\n");
  cpu_time = ( (double) (end_clocks[i] - start_clocks[i]) ) / CLOCKS_PER_SEC;
  printf("Total execution time: \t\t %lf seconds \n", cpu_time);
  cpu_time = cpu_time / (double) number_of_iterations; // time per iteration
  printf("Per iteration execution time: \t %lf seconds \n", cpu_time);
  printf("=========================================\n");
  }

  // ============================================
  // Freeing matrices before ending the code
  // ============================================
  for (int i = 0; i < NUMTESTS; i++) {
    free(mats_a[i]);
  }
}

void test_matrix_shapes(){
  int NUMTESTS = 4;
  int OUTROWS[4] = {125, 250, 500, 1000};
  int OUTCOLS[4] = {125, 250, 500, 1000};
  int INCOLS [4] = {2000, 1000, 500, 250};

  clock_t start_clock;
  clock_t end_clock;

  clock_t start_clock2;
  clock_t end_clock2;

  double cpu_time;

  int number_of_iterations = 30; // TODO: Set this for consistent results


  for (int T = 0; T < NUMTESTS; T++){
    int MATRIX_ROWS_B = OUTROWS[T];
    int MATRIX_COLS_B = INCOLS[T]; // for a non-square matrix

    int MATRIX_ROWS_C = MATRIX_COLS_B;
    int MATRIX_COLS_C = OUTCOLS[T]; // for a non-square matrix


    float * mat_a  = generate_output(MATRIX_ROWS_B, MATRIX_COLS_C);
    float * mat_a2  = generate_output(MATRIX_ROWS_B, MATRIX_COLS_C);
    float * mat_b = generate_rand_input(MATRIX_ROWS_B, MATRIX_COLS_B);
    float * mat_c = generate_rand_input(MATRIX_ROWS_C, MATRIX_COLS_C);

    // ============================================
    // Running and profiling (I decided not to generate a new radom matrix per iteration)
    // ============================================


    start_clock = clock();
    for (int iter = 0; iter < number_of_iterations; iter++) {
      naivemm(mat_a,  mat_b, mat_c, MATRIX_ROWS_B, MATRIX_COLS_C, MATRIX_COLS_B, 0, 0, 0);
    }
    end_clock = clock();

    start_clock2 = clock();
    for (int iter = 0; iter < number_of_iterations; iter++) {
      tiledmm(mat_a2,  mat_b, mat_c, MATRIX_ROWS_B, MATRIX_COLS_C, MATRIX_COLS_B, 60);
    }
    end_clock2 = clock();


    // Print final output matrix for debugging purposes. Can comment out if not
    // needed.

    //print_mat(mat_a, MATRIX_ROWS_B, MATRIX_COLS_C);
    //print_mat(mat_a2, MATRIX_ROWS_B, MATRIX_COLS_C);

    // Verify that optimized tiled implementation is
    // also correct.
    if ( compare_matrices(mat_a, mat_a2, MATRIX_ROWS_B, MATRIX_COLS_C) ) {
      printf("Matrix multiplication is functionally correct.\n");
    } else {
      printf("[Error] Matrix multiplication is not functionally correct...\n");
    }


    // Compute execution time.
    printf("Naive: %d by %d x %d by %d  \n", MATRIX_ROWS_B, MATRIX_COLS_B, MATRIX_ROWS_C, MATRIX_COLS_C);
    printf("=========================================\n");
    cpu_time = ( (double) (end_clock - start_clock) ) / CLOCKS_PER_SEC;
    printf("Total execution time: \t\t %lf seconds \n", cpu_time);
    cpu_time = cpu_time / (double) number_of_iterations; // time per iteration
    printf("Per iteration execution time: \t %lf seconds \n", cpu_time);
    printf("=========================================\n");

    printf("Tiled: %d by %d x %d by %d  \n", MATRIX_ROWS_B, MATRIX_COLS_B, MATRIX_ROWS_C, MATRIX_COLS_C);
    printf("=========================================\n");
    cpu_time = ( (double) (end_clock2 - start_clock2) ) / CLOCKS_PER_SEC;
    printf("Total execution time: \t\t %lf seconds \n", cpu_time);
    cpu_time = cpu_time / (double) number_of_iterations; // time per iteration
    printf("Per iteration execution time: \t %lf seconds \n", cpu_time);
    printf("=========================================\n");


    // ============================================
    // Freeing matrices before ending the code
    // ============================================
    free(mat_a);
    free(mat_a2);
    free(mat_b);
    free(mat_c);
    }
}


void test_matrix_integer_size(){
  clock_t start_clock;
  clock_t end_clock;

  clock_t start_clock2;
  clock_t end_clock2;

  double cpu_time;

  int number_of_iterations = 5; // TODO: Set this for consistent results

  int MATRIX_ROWS_B = 512;
  int MATRIX_COLS_B = 512; // for a square matrix

  int MATRIX_ROWS_C = 512;
  int MATRIX_COLS_C = 512; // for a square matrix

  // Naive
  float * mat_a  = generate_output(MATRIX_ROWS_B, MATRIX_COLS_C);
  int16_t * mat_a2  = generate_output_int16(MATRIX_ROWS_B, MATRIX_COLS_C);
  int8_t * mat_a3  = generate_output_int8(MATRIX_ROWS_B, MATRIX_COLS_C);

  // Tiled
  float * mat_a4  = generate_output(MATRIX_ROWS_B, MATRIX_COLS_C);
  int16_t * mat_a5  = generate_output_int16(MATRIX_ROWS_B, MATRIX_COLS_C);
  int8_t * mat_a6  = generate_output_int8(MATRIX_ROWS_B, MATRIX_COLS_C);

  float * mat_b = generate_rand_input(MATRIX_ROWS_B, MATRIX_COLS_B);
  int16_t * mat_b_int16 = generate_rand_input_int16(MATRIX_ROWS_B, MATRIX_COLS_B);
  int8_t * mat_b_int8 = generate_rand_input_int8(MATRIX_ROWS_B, MATRIX_COLS_B);

  float * mat_c = generate_rand_input(MATRIX_ROWS_C, MATRIX_COLS_C);
  int16_t * mat_c_int16 = generate_rand_input_int16(MATRIX_ROWS_C, MATRIX_COLS_C);
  int8_t * mat_c_int8 = generate_rand_input_int8(MATRIX_ROWS_C, MATRIX_COLS_C);


  // ============================================
  // Running and profiling (I decided not to generate a new radom matrix per iteration)
  // ============================================

  start_clock = clock();
  for (int iter = 0; iter < number_of_iterations; iter++) {
    naivemm(mat_a,  mat_b, mat_c, MATRIX_ROWS_B, MATRIX_COLS_C, MATRIX_COLS_B, 0, 0, 0);
  }
  end_clock = clock();

  start_clock2 = clock();
  for (int iter = 0; iter < number_of_iterations; iter++) {
    tiledmm(mat_a4,  mat_b, mat_c, MATRIX_ROWS_B, MATRIX_COLS_C, MATRIX_COLS_B, 128);
  }
  end_clock2 = clock();

  if ( compare_matrices(mat_a, mat_a4, MATRIX_ROWS_B, MATRIX_COLS_C) ) {
    printf("Matrix multiplication is functionally correct.\n");
  } else {
    printf("[Error] Matrix multiplication is not functionally correct...\n");
  }

  // Compute execution time.
  printf("Naive 32");
  printf("=========================================\n");
  cpu_time = ( (double) (end_clock - start_clock) ) / CLOCKS_PER_SEC;
  printf("Total execution time: \t\t %lf seconds \n", cpu_time);
  cpu_time = cpu_time / (double) number_of_iterations; // time per iteration
  printf("Per iteration execution time: \t %lf seconds \n", cpu_time);
  printf("=========================================\n");

  printf("Tilted 32");
  printf("=========================================\n");
  cpu_time = ( (double) (end_clock2 - start_clock2) ) / CLOCKS_PER_SEC;
  printf("Total execution time: \t\t %lf seconds \n", cpu_time);
  cpu_time = cpu_time / (double) number_of_iterations; // time per iteration
  printf("Per iteration execution time: \t %lf seconds \n", cpu_time);
  printf("=========================================\n");

  start_clock = clock();
  for (int iter = 0; iter < number_of_iterations; iter++) {
    naivemm_int16(mat_a2,  mat_b_int16, mat_c_int16, MATRIX_ROWS_B, MATRIX_COLS_C, MATRIX_COLS_B, 0, 0, 0);
  }
  end_clock = clock();

  start_clock2 = clock();
  for (int iter = 0; iter < number_of_iterations; iter++) {
    tiledmm_int16(mat_a5,  mat_b_int16, mat_c_int16, MATRIX_ROWS_B, MATRIX_COLS_C, MATRIX_COLS_B, 128);
  }
  end_clock2 = clock();

  if ( compare_matrices_int16(mat_a2, mat_a5, MATRIX_ROWS_B, MATRIX_COLS_C) ) {
    printf("Matrix multiplication is functionally correct.\n");
  } else {
    printf("[Error] Matrix multiplication is not functionally correct...\n");
  }

  // Compute execution time.
  printf("Naive 16");
  printf("=========================================\n");
  cpu_time = ( (double) (end_clock - start_clock) ) / CLOCKS_PER_SEC;
  printf("Total execution time: \t\t %lf seconds \n", cpu_time);
  cpu_time = cpu_time / (double) number_of_iterations; // time per iteration
  printf("Per iteration execution time: \t %lf seconds \n", cpu_time);
  printf("=========================================\n");

  printf("Tilted 16");
  printf("=========================================\n");
  cpu_time = ( (double) (end_clock2 - start_clock2) ) / CLOCKS_PER_SEC;
  printf("Total execution time: \t\t %lf seconds \n", cpu_time);
  cpu_time = cpu_time / (double) number_of_iterations; // time per iteration
  printf("Per iteration execution time: \t %lf seconds \n", cpu_time);
  printf("=========================================\n");

  start_clock = clock();
  for (int iter = 0; iter < number_of_iterations; iter++) {
    naivemm_int8(mat_a3,  mat_b_int8, mat_c_int8, MATRIX_ROWS_B, MATRIX_COLS_C, MATRIX_COLS_B, 0, 0, 0);
  }
  end_clock = clock();

  start_clock2 = clock();
  for (int iter = 0; iter < number_of_iterations; iter++) {
    tiledmm_int8(mat_a6,  mat_b_int8, mat_c_int8, MATRIX_ROWS_B, MATRIX_COLS_C, MATRIX_COLS_B, 128);
  }
  end_clock2 = clock();

  if ( compare_matrices_int8(mat_a3, mat_a6, MATRIX_ROWS_B, MATRIX_COLS_C) ) {
    printf("Matrix multiplication is functionally correct.\n");
  } else {
    printf("[Error] Matrix multiplication is not functionally correct...\n");
  }

  // Compute execution time.
  printf("Naive 8");
  printf("=========================================\n");
  cpu_time = ( (double) (end_clock - start_clock) ) / CLOCKS_PER_SEC;
  printf("Total execution time: \t\t %lf seconds \n", cpu_time);
  cpu_time = cpu_time / (double) number_of_iterations; // time per iteration
  printf("Per iteration execution time: \t %lf seconds \n", cpu_time);
  printf("=========================================\n");

  printf("Tilted 8");
  printf("=========================================\n");
  cpu_time = ( (double) (end_clock2 - start_clock2) ) / CLOCKS_PER_SEC;
  printf("Total execution time: \t\t %lf seconds \n", cpu_time);
  cpu_time = cpu_time / (double) number_of_iterations; // time per iteration
  printf("Per iteration execution time: \t %lf seconds \n", cpu_time);
  printf("=========================================\n");

  // ============================================
  // Freeing matrices before ending the code
  // ============================================
  free(mat_a);
  free(mat_a2);
  free(mat_a3);
  free(mat_a4);
  free(mat_a5);
  free(mat_a6);
  free(mat_b);
  free(mat_b_int16);
  free(mat_b_int8);
  free(mat_c);
  free(mat_c_int16);
  free(mat_c_int8);
}

int main() {
  test_matrix_sizes();
  test_matrix_shapes();
  test_matrix_integer_size();
  return 0;
}