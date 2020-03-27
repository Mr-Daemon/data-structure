//
// Created by cyb12 on 2020-02-03.
//

class test {
public:
    struct hello {
        int a, b;
    };
};

int main(int argc, char const *argv[]) {
    typename test::hello hi = {1, 2};
    return 0;
}
