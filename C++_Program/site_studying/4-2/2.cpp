#include <iostream>
#include <cmath>
#include <limits> // INFINITY 사용을 위해 추가

class Point {
    int x, y;

public:
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    int get_x() const { return x; }
    int get_y() const { return y; }
};

class Geometry {
    int num_points;
    Point* point_array[100];

public:
    Geometry() {
        num_points = 0;
    }
    ~Geometry() {
        for (int i = 0; i < num_points; ++i)
            delete point_array[i];
    }
    void AddPoint(const Point& point) {
        point_array[num_points++] = new Point(point.get_x(), point.get_y());
    }
    void PrintPoints();
    void PrintDistance();
    void PrintNumMeets();
};

void Geometry::PrintPoints() {
    for (int i = 0; i < num_points; i++) {
        std::cout << "x: " << point_array[i]->get_x();
        std::cout << ", y: " << point_array[i]->get_y() << std::endl;
    }
}

void Geometry::PrintDistance() {
    for (int i = 0; i < num_points; i++) {
        int pos1_x = point_array[i]->get_x();
        int pos1_y = point_array[i]->get_y();
        for (int j = i + 1; j < num_points; j++) {
            int pos2_x = point_array[j]->get_x();
            int pos2_y = point_array[j]->get_y();
            double distance = sqrt(pow(pos1_x - pos2_x, 2) + pow(pos1_y - pos2_y, 2));
            std::cout << "Distance between pos" << (i + 1) << " and pos" << (j + 1) << " is " << distance << std::endl;
        }
    }
}

void Geometry::PrintNumMeets() {
    int num_line = num_points * (num_points - 1) / 2;
    float* slope = new float[num_line]; // 기울기 저장 배열
    int idx = 0;

    for (int i = 0; i < num_points; i++) {
        int pos1_x = point_array[i]->get_x();
        int pos1_y = point_array[i]->get_y();
        for (int j = i + 1; j < num_points; j++) {
            int pos2_x = point_array[j]->get_x(); // 수정됨
            int pos2_y = point_array[j]->get_y(); // 수정됨

            if (pos2_x - pos1_x == 0) {
                slope[idx] = std::numeric_limits<float>::infinity(); // x 좌표가 같을 경우, 수직선(INF) 처리
            } else {
                slope[idx] = static_cast<float>(pos2_y - pos1_y) / (pos2_x - pos1_x); // 기울기 계산
            }
            idx++;
        }
    }

    if (num_line != idx)
        std::cout << "error" << std::endl;

    int num_meets = 0;
    for (int i = 0; i < num_line; i++) {
        for (int j = i + 1; j < num_line; j++) {
            if (slope[i] != slope[j])
                num_meets++;
        }
    }

    std::cout << "Number of intersection points: " << num_meets << std::endl;

    delete[] slope;
}

int main() {
    Point pos1(2, 3);
    Point pos2(3, 4);
    Point pos3(4, 5);
    Point pos4(2, 7); // x 좌표가 pos1과 같아 예외 발생 가능

    Geometry geometry;
    geometry.AddPoint(pos1);
    geometry.AddPoint(pos2);
    geometry.AddPoint(pos3);
    geometry.AddPoint(pos4); // 추가된 점

    geometry.PrintPoints();
    geometry.PrintDistance();
    geometry.PrintNumMeets();

    return 0;
}