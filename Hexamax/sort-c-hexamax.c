#include <string.h>

void sort(unsigned int *nums, int n) {
  unsigned int *ult= &nums[n-1];
  unsigned int *p= nums;
  while (p<ult) {
    // No modifique nada arriba de esta linea
    // Inicio de la parte que debe cambiar
    // No modifique nada arriba de esta linea
    // Inicio de la parte que debe cambiar
    int mask = 0xF;
    int p0 = p[0];
    int p1 = p[1];
    int m_p0 = 0;
    int m_p1 = 0;    
    for (int i=0; i<8; i++){
        int p0_mask = p0 & mask;
        if((p0_mask) > m_p0){
            m_p0 = p0_mask;
        }
        int p1_mask = p1 & mask;
        if((p1_mask) > m_p1){
            m_p1 = p1_mask;
        }
        p0 = p0>>4;
        p1 = p1>>4;
    }
    int t1= m_p1 <= m_p0 ? 0 : 1;
    // Fin de la parte que debe cambiar
    // No Cambie nada mas a partir de aca
    if (t1 <= 0)
      p++;
    else {
      unsigned int tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= nums;
    }
  }
}
