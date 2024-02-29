#include "test.hpp"

#include "Matrix.hpp"
#include "Vector.hpp"

using namespace std;
using namespace EngineJ::math::matrix;
using namespace EngineJ::math::matrix::test;

bool floatComp(float a, float b, float threshold = 0.001) {
    return abs(a - b) < threshold;
}

std::vector<Test> tests{
    {
        "Init, assign and access MatMN",
        []()->bool {
            MatMN mat{5, 2};

            mat({
                1.0, 2.0,
                2.0, 4.0,
                4.0, 8.0,
                8.0, 16.0,
                16.0, 32.0
            });

            // for (int i = 0; i < 10; i++) {
            //     cout << "(" << i / 2 << "," << i % 2 << ") " << mat[i / 2][i % 2] << endl;
            // }

            return floatComp(mat[0][0], 1.0) && floatComp(mat[0][1], 2.0) && floatComp(mat[4][0], 16.0);// && floatComp(mat[4][1], 32.0);
        }
    },
    {
        "MatMN fills internal data structure correctly #1",
        []()->bool {
            MatMN mat{5, 2};

            mat({
                1.0, 2.0,
                2.0, 4.0,
                4.0, 8.0,
                8.0, 16.0,
                16.0, 32.0
            });

            float* arr[] = {
                mat[0],
                mat[1],
                mat[2],
                mat[3],
                mat[4]
            };

            bool result = true;

            for (int i = 1; i < 5; i++) {
                // printf("Row %d: %i, Diff: %f\n", i, (int)arr[i], (float)((int)arr[i] - (int)arr[i - 1]) / sizeof(float));
                result *= floatComp((float)((int)arr[i] - (int)arr[i - 1]) / sizeof(float), 2.0);
            }

            return result;
        }
    },
    {
        "MatMN fills internal data structure correctly #2",
        []()->bool {
            MatMN mat{4, 5};

            mat({
                1.0, 2.0, 3.0, 4.0, 5.0,
                2.0, 4.0, 6.0, 8.0, 16.0,
                4.0, 8.0, 12.0, 16.0, 32.0,
                8.0, 16.0, 24.0, 32.0, 64.0
            });

            float* arr[] = {
                mat[0],
                mat[1],
                mat[2],
                mat[3]
            };

            bool result = true;

            for (int i = 1; i < 4; i++) {
                // printf("Row %d: %i, Diff: %f\n", i, (int)arr[i], (float)((int)arr[i] - (int)arr[i - 1]) / sizeof(float));
                result *= floatComp((float)((int)arr[i] - (int)arr[i - 1]) / sizeof(float), 5.0);
            }

            return result;
        }
    },
    {
        "Init, assign and access MatN",
        []()->bool {
            MatN mat{3};

            mat({
                1.0, 2.0, 3.0,
                2.0, 4.0, 6.0,
                4.0, 8.0, 12.0
            });

            return floatComp(mat[0][0], 1.0) && floatComp(mat[0][2], 3.0) && floatComp(mat[1][1], 4.0) && floatComp(mat[2][2], 12.0);
        }
    },
    {
        "Init, assign and access Mat2",
        []()->bool {
            Mat2 mat{
                1.0, 2.0,
                2.0, 4.0
            };

            return floatComp(mat[0][0], 1.0) && floatComp(mat[0][1], 2.0) && floatComp(mat[1][0], 2.0) && floatComp(mat[1][1], 4.0);
        }
    },
    {
        "Init, assign and access Mat3",
        []()->bool {
            Mat3 mat{
                1.0, 2.0, 3.0,
                2.0, 4.0, 6.0,
                4.0, 8.0, 12.0
            };

            return floatComp(mat[0][0], 1.0) && floatComp(mat[0][2], 3.0) && floatComp(mat[1][1], 4.0) && floatComp(mat[2][2], 12.0);
        }
    },
    {
        "Init, assign and access Mat4",
        []()->bool {
            Mat4 mat{
                1.0, 2.0, 3.0, 4.0,
                2.0, 4.0, 6.0, 8.0,
                4.0, 8.0, 12.0, 16.0,
                8.0, 16.0, 24.0, 32.0
            };

            return floatComp(mat[0][0], 1.0) && floatComp(mat[0][3], 4.0) && floatComp(mat[3][1], 16.0) && floatComp(mat[3][3], 32.0);
        }
    },
    {
        "2x3 * 3x5 (= 2x5)",
        []()->bool {
            MatMN mat1{2, 3};
            mat1({
                1.0, 2.0, 3.0,
                4.0, 8.0, 12.0
            });

            MatMN mat2{3, 5};
            mat2({
                1.0, 2.0, 3.0, 3.4, 4.6,
                4.0, 8.0, 12.0, 4.6, 3.7,
                34.0, 5.0, 43.0, 3.0, 1.0
            });

            MatMN result = mat1 * mat2;

            return result.NumRows() == 2 && result.NumCols() == 5;
        }
    },
    {
        "4x4 * 4x1 (= 4x1)",
        []()->bool {
            MatMN mat1{4, 4};
            mat1({
                1.0, 2.0, 3.0, 3.4,
                4.0, 8.0, 12.0, 4.6,
                34.0, 5.0, 43.0, 3.0,
                4.0, 8.0, 12.0, 4.6
            });

            MatMN mat2{4, 1};
            mat2({ 1.0, 2.0, 3.0, 3.4 });

            MatMN result = mat1 * mat2;

            return result.NumRows() == 4 && result.NumCols() == 1;
        }
    },
    {
        "2x2 * 2x2 (= 2x2)",
        []()->bool {
            Mat2 mat1{
                1.0, 2.0,
                3.0, 3.4
            };

            Mat2 mat2{
                4.0, 7.0,
                8.0, 16.0
            };

            Mat2 result1 = mat1 * mat2;
            Mat2 result2 = mat1 * mat2;

            return result1.NumRows() == 2 && result1.NumCols() == 2 && result2.NumRows() == 2 && result2.NumCols() == 2;
        }
    },
    {
        "2x2 * 3x3 (= exception)",
        []()->bool {
            try {
                Mat2 mat1{
                    1.0, 2.0,
                    3.0, 3.4
                };

                Mat3 mat2{
                    4.0, 7.0, 3.0,
                    8.0, 16.0, 3.5,
                    2.5, 6.7, 8.2
                };

                MatMN result1 = (MatMN&)mat1 * (MatMN&)mat2;
            }
            catch (const exception& e) {
                return true;
            }

            return false;
        }
    },
    {
        "Init, assign and access VecN",
        []()->bool {
            VecN vec(5);
            vec({ 1.0, 2.0, 3.0, 4.0, 5.0 });

            // cout << vec[0] << " " << vec[1] << " " << vec[2] << " " << vec[3] << " " << vec[4] << endl;

            return floatComp(vec[0], 1.0) && floatComp(vec[1], 2.0) && floatComp(vec[2], 3.0);
        }
    },
    {
        "Init, assign and access Vec2",
        []()->bool {
            Vec2 vec{ 1.0, 2.0 };

            return vec[0] == 1.0 && vec[1] == 2.0;
        }
    },
    {
        "Init, assign and access Vec3",
        []()->bool {
            Vec3 vec{ 1.0, 2.0, 3.0 };

            return vec[0] == 1.0 && vec[1] == 2.0 && vec[2] == 3.0;
        }
    },
    {
        "Init, assign and access Vec4",
        []()->bool {
            Vec4 vec{ 1.0, 2.0, 3.0, 4.0 };

            return vec[0] == 1.0 && vec[1] == 2.0 && vec[2] == 3.0 && vec[3] == 4.0;
        }
    },
    {
        "2x4 * v4",
        []()->bool {
            MatMN mat {2,4};
            mat({
                1.0, 2.0, 3.0, 4.0,
                2.0, 4.0, 8.0, 16.0
            });

            Vec4 vec{ 1.0, 2.0, 3.0, 4.0 };

            Vec2 result = Vec2(mat * vec);

            bool dims = result.NumRows() == 2 && result.NumCols() == 1;
            bool nums = floatComp(result[0], 30.0) && floatComp(result[1], 98.0);

            result.Log("Result");

            return dims && nums;
        }
    },
};

bool EngineJ::math::matrix::test::runTests() {
    int testsFailed = 0;

    cout << endl << "RUNNING TESTS" << endl << endl;

    for (Test& t : tests) {
        try {
            cout << "RUNNING TEST: " << t.description << endl;

            if (!t.condition()) {
                testsFailed++;
                cout << "   TEST FAILED!" << endl;
            }
        }
        catch (exception e) {
            testsFailed++;

            cout << "   EXCEPTION: " << e.what() << endl;
        }
    }

    if (testsFailed) cout << endl << testsFailed << " TEST(S) FAILED" << endl;
    else cout << endl << "ALL TEST(S) PASSED" << endl;

    return !testsFailed;
}