#!/usr/bin/python3
""" Unit test for calc.py """
import inspect
import unittest
import calc

class TestCalc(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        """ called at the start of TestCalc """
        print(inspect.stack()[0][3])

    @classmethod
    def tearDownClass(cls):
        """ called at the end of TestCalc """
        print('tearDownClass')


    def setUp(self):
        """ called at the start of each function """
        print(inspect.stack()[0][3])

    def tearDown(self):
        """ called at the end of each function """
        print('tearDown')

    def test_add(self):
        print(inspect.stack()[0][3])
        self.assertEqual(calc.add(10, 5), 15)
        self.assertEqual(calc.add(-1, 1), 0)
        self.assertEqual(calc.add(-1, -1), -2)

    def test_subtract(self):
        print(inspect.stack()[0][3])
        self.assertEqual(calc.subtract(10, 5), 5)
        self.assertEqual(calc.subtract(-1, 1), -2)
        self.assertEqual(calc.subtract(-1, -1), 0)

    def test_multiply(self):
        print(inspect.stack()[0][3])
        self.assertEqual(calc.multiply(10, 5), 50)
        self.assertEqual(calc.multiply(-1, 1), -1)
        self.assertEqual(calc.multiply(-1, -1), 1)

    def test_divide(self):
        print(inspect.stack()[0][3])
        self.assertEqual(calc.divide(10, 5), 2)
        self.assertEqual(calc.divide(-1, 1), -1)
        self.assertEqual(calc.divide(-1, -1), 1)
        self.assertEqual(calc.divide(7, 2.0), 3.5)

        self.assertRaises(ValueError, calc.divide, 10, 0)


if __name__ == '__main__':
    unittest.main()

