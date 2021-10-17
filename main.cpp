
#include "scene/bsp_tree.hpp"
#include "tests/test_interception.hpp"
#include <vector>
#include <iostream>

//std::vector - это вроде как динамический массив
std::vector<rytg::Triangle> parseTriangles(){
    size_t N = 0;
    // Вводим количество треугольников
    std::cin >> N;
    // насколько я понял, создаём динамический массив result размером N, в котором хранятся треугольники
    std::vector<rytg::Triangle> result(N);
    double x, y, z;
    // Считываем N наборов точек - вершин треугольников
    for(size_t i = 0; i < N; ++i){
        rytg::Point p1, p2, p3;
        std::cin >> x >> y >> z;
        p1 = {x, y, z};
        std::cin >> x >> y >> z;
        p2 = {x, y, z};
        std::cin >> x >> y >> z;
        p3 = {x, y, z};
        // Сохраняем в динамический массив треугольник
        result[i] = rytg::Triangle(p1, p2, p3);
    }
    // Возвращаем массив(мб указатель или ссылку)
    return result;
}


int main(){
    std::cout << "RayTraycing" << std::endl;
    // Автоматически определяется тип для v
    auto v = parseTriangles();
    // На основе всего массива введённых треугольников строим BSP tree
    // Насколько понял, вызывается конструктор
    rytg::BSPtree bsp(v);
    int x;
    //test_rytg::test_interception();
    return 0;
}
