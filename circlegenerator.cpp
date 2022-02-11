#include <iostream>
#include <cmath>
#include <vector>

struct Settings {
    bool isHollow = false;
    char blank = ' ';
    char outline = 'O';
    char infill = 'O';
    int thickness = 1;
    int diameter = 24;
};

class Generation {
private:
    std::vector<char> data_;
    size_t size_ = 0;
    size_t width_ = 0;
public:
    Generation(){};
    Generation(const Generation& generation) {
        size_ = generation.size_;
        width_ = generation.width_;
        data_.resize(size_, ' ');
        for (size_t i = 0; i < size_; i++) {
            data_[i] = (generation.data_)[i];
        }
    }
    Generation(const Settings& settings) {
        size_ = settings.diameter * settings.diameter;
        width_ = settings.diameter;
        data_.resize(size_, ' ');
        for (size_t i = 0; i < size_; i++) {
            data_[i] = settings.blank;
        }
    }
    void print() {
        for (size_t i = 0; i < width_; i++) {
            for (size_t j = 0; j < width_; j++) {
                std::cout << data_[i * width_ + j];
            }
            std::cout << '\n';
        }
}
    size_t width() {
        return width_;
    }
    void setWidth(size_t width) {
        //clears data
        size_ = width * width;
        width_ = width;
        data_.resize(size_, ' ');
        for (size_t i = 0; i < size_; i++) {
            data_[i] = ' ';//TODO: Increase Efficiency by not writing over newly allocated elements that already were assigned ' '
        }
    }
    void setPx(size_t row, size_t col, char val) {
        data_[row * width_ + col] = val;
    }
};

class Circle {
public: 
    Settings settings;
    mutable Generation generation; //this should always be freshly generated or when new settings are applied to avoid unexpected behavior
    void generate() const {
        if (generation.width() != settings.diameter) generation.setWidth(settings.diameter);
        float centerpoint = (float)settings.diameter / 2;
        for (size_t i = 0; i < settings.diameter; i++) {
            for (size_t j = 0; j < settings.diameter; j++) {
                float dist = sqrt((centerpoint - ((float)i + 0.5)) * (centerpoint - ((float)i + 0.5)) + (centerpoint - ((float)j + 0.5)) * (centerpoint - ((float)j + 0.5)));
                if (dist > centerpoint/*THIS centerpoint VAR MEANS AND IS ACTUALLY THE SAME AS RADIUS*/) {
                    generation.setPx(i, j, settings.blank); continue;
                }
                if (dist > centerpoint - (float)settings.thickness) {
                    generation.setPx(i, j, settings.outline); continue;
                }
                //else {
                    generation.setPx(i, j, settings.isHollow ? settings.blank : settings.infill); continue;
                //}
            }
        }
    }
};

int main()
{
    Circle circle;
    std::cout << "Welcome to the Instant Circle Generator, easy software to input the size of a circle in pixels that will be automatically drawn it for you.\n";
    while (true) {
        int choice;
        std::cout << "Main Menu (input decision):\n1. Generate and Output Circle\n2. Change Settings\n" << "Choice:";
        std::cin >> choice;
        switch (choice) {
            case 1: {
                circle.generate();
                circle.generation.print();
                break;
                }
            case 2: {
                int choice2;
                std::cout << "Change Setting (input decision):\n1. Diameter\n2. Thickness\n3. Hollow/Solid\n4. Blank Character\n5. Outline Character\n6. Infill Character\n7. Back\n" << "Choice:";
                std::cin >> choice2;
                switch (choice2) {
                case 1: {std::cout << "Enter New Diameter\n"; int diameter; std::cin >> diameter; circle.settings.diameter = diameter; break; }
                case 2: {std::cout << "Enter New Thickness\n"; int thickness; std::cin >> thickness; circle.settings.thickness = thickness; break; }
                case 3: {std::cout << "Hollow/Solid (input decision):\n1. Solid\n2. Hollow\n"; int isHollow; std::cin >> isHollow; circle.settings.isHollow = isHollow - 1; break; }
                case 4: {std::cout << "Enter New Blank Character\n"; char blank; std::cin >> blank; circle.settings.blank = blank; break; }
                case 5: {std::cout << "Enter New Outline Character\n"; char outline; std::cin >> outline; circle.settings.outline = outline; break; }
                case 6: {std::cout << "Enter New Infill Character\n"; char infill; std::cin >> infill; circle.settings.infill = infill; break; }
                case 7: {break; }
                default: {std::cout << "Invalid Decision"; }
                }
                break;
            }
            default: {
                std::cout << "Invalid Decision\n";
            }
        }
    }
}