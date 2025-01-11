//void swap(int* a, int* b) {
//	int t = *a;
//	*a = *b;
//	*b = t;
//}

//void swap(int* a, int* b) {
//    if (a != b) {
//        *a = *a + *b;
//        *b = *a - *b;
//        *a = *a - *b;
//    }
//}

void swap(int* a, int* b) {
    if (a != b) {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}