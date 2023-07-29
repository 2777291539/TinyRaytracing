#include "vec3.h"
#include "ray.h"

#include <iostream>

bool hit_sphere(const vec3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0  * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

vec3 ray_color(const ray& r) {
    if (hit_sphere(vec3(0,0,-100), 25, r))
        return vec3(1, 0, 0);
    // 此处，我们将输入的光线的方向被标准化。即范围在 [-1,1] 之间
    // 即它的方向是一个单位圆向量
    // vec3 unit_direction = unit_vector(r.direction());

    // 再将它的 y 分量转化为 [0,1] 范围
    auto t = 0.5*(r.dir.y() + 1.0);

    // 认为图像的最下面是 0，最上面是 1，然后根据 y 进行插值
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}


int main() {
    // 设置图像的宽和高
    constexpr int image_width = 200;
    constexpr int image_height = 100;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    // 行优先，从上到下遍历整个图像的像素
    // 我们认为，左下角是 0,0 点
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            // 获取像素坐标(并未中心点)，并将其归一化
            // auto u = double(i) / image_width;
            // auto v = double(j) / image_height;

            // 生成射线
            // 我们认为原点是 0,0,0，然后二维空间下，图像的左下角实际是-x/2, -y/2
            // 获取射线的方向的办法：像素坐标 - 原点坐标，因为原点坐标是 0,0,0，即射线方向就是像素坐标
            // 左下角的坐标可以定义为 (-100, -50, -1)，则任意一点的坐标就是 (i-100, j-50, -1)
            // ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 pos{static_cast<double>(i-100), static_cast<double>(j-50), -100.0};
            ray r(origin, pos);
            vec3 color = ray_color(r);
            color.write_color(std::cout);
        }
    }

    std::cerr << "\nDone.\n";
}
