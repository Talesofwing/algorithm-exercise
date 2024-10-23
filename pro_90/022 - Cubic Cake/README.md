# Cubic Cake(★2)

The source code provides two different implementation methods:

1. Splitting Method: As the name suggests, this method gradually divides the rectangular prism into smaller units until it reaches the shape of a cube. However, this method is relatively inefficient and may lead to excessive time or memory overflow when dealing with large problems, making it unsuitable for this task.

2. GCD (Greatest Common Divisor) Method: This method involves calculating the greatest common divisor of the three sides of the rectangular prism. For example, for a rectangular prism with dimensions(3, 6, 9), the greatest common divisor is 3. By dividing each side length by the GCD, we can determine the number of parts needed to divide the rectangular prism into several cubes. The value obtained by dividing each side length by the GCD indicates how many parts each side is divided into, forming cubes. By subtracting 3 from this number, we can find the total number of splits required.

A commonly used algorithm for solving the greatest common divisor is the [Euclidean Algorithm](https://en.wikipedia.org/wiki/Euclidean_algorithm), which is an efficient and widely used mathematical method for calculating the greatest common divisor of two numbers. In this context, using the GCD method not only significantly improves computational efficiency but also ensures the accuracy of the calculated number of splits.

The reason for subtracting 3 is that the value obtained after dividing by the GCD represents the number of segments created rather than the number of splits needed. For example, to divide one part into two segments, only one split is required. Therefore, we need to subtract 1 for each direction, resulting in a total subtraction of 3.
