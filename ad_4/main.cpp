#include "inc/BMP.hpp"

int main() {

    nu::images::BMP secret(150, 219);
    secret.readFile("test.bmp");

    //secret.superFilter();
    secret.writeSecret();
    secret.writeFile("testing.bmp");

    return 0;
}

//Воспользуйтесь классом для работы с BMP-изображениями и зашифруйте произвольную текстовую информацию.
//О формате BMP http://4a4ik.blogspot.com/2014/08/bmp.html
