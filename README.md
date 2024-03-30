<h1 align="center">Дешифратор :clipboard:

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
</h1>
<h3 align="left">Описание</h3>
Этот код предназначен для дешифровки документа, содержащего наборы чисел, предположительно представляющих собой координаты вершин треугольников. Сам файл представлен в виде документа с расширением ".txt", содержимое же выглядит примерно так:

```
03 9 56 75259 259 25 27 03 10 567 4 23 75259 259 25 27 03 11 567 4 23 75259 259
 03 12 567 4 23 75259 259 67 68 39 988 90 67 03 03 13 567 4 23 5 6    03 14 8 567 678 567 103 480 444
```

Предполагается, что *0x* обозначает количество вершин, а следующим за ним числа - вершины многоугольника. Выдвигается гипотеза, что итоговое пересечение многоугольников является ключом для дешифровки.

---

**Цель:** Найти область пересечения многоугольников.

![result](https://github.com/DeStep3000/IOT/blob/master/results2.png)

## Содержание
- [Технологии](#технологии)
- [Тестирование](#тестирование)
- [Contributing](#contributing)
- [To do](#to-do)
- [Команда проекта](#команда-проекта)

## Технологии
*проект реализован на C++*
- CMake
- GoogleTest
- SFML
- wxWidgets

## Использование
Если вы хотите работать с чистым(без графики) кодом напрямую, то для этого подключите "polygon.h" в main.cpp:
```c++
#include "polygon.h"
int main() {
    return 0;
}
```
Далее, организуем чтение из файла, чтобы считать текст и преобразовать в дальнейшем в поле класса:
```c++
const std::string path = "yourpathtofile\\test.txt";//Абсолютный путь к файлу
std::string input = read_file(path);//чтение из файла
input= edit_file(input);//преобразование данных
```
После, необходимо создать экземпляр класса PolygonField, который реализует работу с "полем" многоугольников:
```c++
PolygonField pn_field;//создаем экземпляр класса
pn_field.input_polygons(input);//Передаем данные
```
Далее вызываем ```intersect_polygon_field_final()``` и сохраняем результат в Polygon:
```c++
pn_field.print_field();//выводим все многоугольники в консоль
Polygon res = pn_field.intersect_polygon_field_final();//пересекаем многоугольники
res.print_vertices();//выводим результат в консоль
```
Если вы хотите более подробно погрузиться в детали читайте [DOCUMENTATION.md](./DOCUMENTATION.md), либо смотрите ```polygon.cpp``` и ```polygon.h```.

### Требования
Для установки и запуска проекта, необходимо скачать библиотеку wxWidgwts c сайта https://www.wxwidgets.org/downloads/ раздел Binaries. Также распвкуйте архивы на корневой диск С.


## Тестирование
Для теcтирования библиотеки использовалась сторонняя библиотека googletest. Чтобы подключить ее, нужно соединить файлы в cmake, например:
```c++
add_executable(Google_Test_readfile_run tests/test_readfile.cpp src/readfile.cpp)
target_link_libraries(Google_Test_readfile_run gtest gtest_main)
```
Примеры тестов можно увидеть в файлах test_polygon.cpp и test_readfile.cpp для тестирования файла polygon.cpp и readfile.cpp соответсвенно. В файле с тестами также надо подключить gtest через ```#include <gtest/gtest.h>```
Пример одного из тестов:
```c++
TEST(intersect_polygon_field_final_test, single_pn_test2) {
    std::string input = "03 1 1 2 3 3 2";
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);
    Polygon res = pn_field.intersect_polygon_field_final();

    std::vector<Point> pn_points{{1, 1}, {2, 3}, {3, 2}};
    EXPECT_EQ(res.get_num_vertices(), 3);
    EXPECT_EQ(res.get_vertices(), pn_points);

    pn_points = {{1.0 + eps, 1}, {2, 3}, {3, 2}};
    for (size_t i = 0; i < pn_points.size(); i++) {
        EXPECT_TRUE(pn_points[i] == res.get_vertices()[i]);
    }
    EXPECT_EQ(res.get_vertices(), pn_points);

    pn_points = {{2, 3}, {1, 1}, {3, 2}};
    EXPECT_NE(res.get_vertices(), pn_points);
}
```
После объвления всех тестов необходимо вызвать функцию main следующим образом:
```c++
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
```

## Contributing
В случае, если вы хотите поучаствовать в нашем проекте, то все условия прописаны в [CONTRIBUTING.md](./CONTRIBUTING.md).

## FAQ 
> Как именно работает библиотека?

Библиотека рассматривает входной файл на предмет *" 0x "*, где x - цифра(1-9), затем считывает числа после символа, считая, что это координаты некоторого многоугольника. Затем находится пересечение итоговое всех многоугольников.

### Зачем вы разработали этот проект?
Проектная работа в рамках курса "Технологии программирования (язык программирования С++)" студентов НИУ ВШЭ НН. Основная цель нашего проекта - командная работа (отношения в команде, распределение обязанностей), работа с Github, работа с библиотеками (GoogleTest, SFML)

## To do
- [x] Добавить крутое README
- [x] Жестко затестить код
- [x] Достроить нахождение площади
- [x] Подправить лицензию
- [x] Добавить менеджер файлов
- [x] Дописать readme
- [x] Досторить многоугольники
      

## Команда проекта

- [Даниил Холяк](https://github.com/limoncatGod) - Backend (основная структура математического кода) + Team leader 
- [Андрей Подвигин](https://github.com/dragonpuffle) - Testing + File decoding (работа с GoogleTest) 
- [Денис Степанов](https://github.com/DeStep3000) - Code Organization + Graphics (CMake, Github)
- [Алина Гайсина](https://github.com/VVroli) - Testing + Public Relations + Graphics

  Для обратной связи вы можете написать нашему менеджеру - [Алина Гайсина](https://t.me/VVroli)
## Источники
- Райан Гослинг
- Дарт Вейдер
