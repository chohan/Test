package com.chohan;

import java.util.List;
import java.util.Arrays;
import java.util.stream.Collectors;

public class StreamFuncs {


	public static void test() {
		List<String> numbers_str = Arrays.asList("1", "2", "3", "4", "5", "6");
		System.out.println("Input numbers in strings: " + numbers_str);
		List<Integer> numbers = 
				numbers_str.stream()
        	.map(Integer::valueOf)		// Convert String to Integer
					.collect(Collectors.toList());
		System.out.println("Integer: " + numbers);

		// filter only even numbers
		System.out.println("Even number: " + numbers.stream()
					.filter(n -> n%2 == 0)
					.collect(Collectors.toList()));
		
		// take sum
		System.out.println("Sum of numbers: " + numbers.stream().reduce(0, (a, b) -> a + b));
		
		// sum of all even numbers in one go
		System.out.println("Sum of all even numbers: " +
			numbers_str.stream()
			.map(Integer::valueOf)
			.filter(n -> n%2 == 0)
			.reduce(0, (a,b) -> a+b)); 

	}

}

