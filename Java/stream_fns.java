package com.chohan



List<String> numbers = Arrays.asList("1", "2", "3", "4", "5", "6");
List<Integer> evenNumbers = numbers.stream()
                                   .map(Integer::valueOf)          // Convert String to Integer
                                   .filter(n -> n % 2 == 0)        // Keep even numbers only
                                   .collect(Collectors.toList());  // Collect results into a List




