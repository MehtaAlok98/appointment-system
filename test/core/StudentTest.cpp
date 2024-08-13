#include <gtest/gtest.h>
#include "core/Student.hpp"

TEST(StudentTest, SetAndGetAttributes)
{
  Student s;
  s.setNumber("123");
  s.setName("John");
  s.setSurname("Doe");
  s.setDepartment("Computer Science");
  s.setYear("2024");
  s.setEmail("john.doe@example.com");
  s.setPhone("123-456-7890");

  EXPECT_EQ(s.getNumber(), "123");
  EXPECT_EQ(s.getName(), "John");
  EXPECT_EQ(s.getSurname(), "Doe");
  EXPECT_EQ(s.getDepartment(), "Computer Science");
  EXPECT_EQ(s.getYear(), "2024");
  EXPECT_EQ(s.getEmail(), "john.doe@example.com");
  EXPECT_EQ(s.getPhone(), "123-456-7890");
}

// Test setting and getting the student's email
TEST(StudentTest, SetAndGetEmail)
{
  Student student;
  student.setEmail("jane.doe@example.com");
  EXPECT_EQ(student.getEmail(), "jane.doe@example.com");
}

// Test setting and getting the student's phone number
TEST(StudentTest, SetAndGetPhone)
{
  Student student;
  student.setPhone("987-654-3210");
  EXPECT_EQ(student.getPhone(), "987-654-3210");
}

// Test setting and getting empty strings
TEST(StudentTest, SetEmptyStrings)
{
  Student student;
  student.setNumber("");
  student.setName("");
  student.setSurname("");
  student.setDepartment("");
  student.setYear("");
  student.setEmail("");
  student.setPhone("");

  EXPECT_EQ(student.getNumber(), "");
  EXPECT_EQ(student.getName(), "");
  EXPECT_EQ(student.getSurname(), "");
  EXPECT_EQ(student.getDepartment(), "");
  EXPECT_EQ(student.getYear(), "");
  EXPECT_EQ(student.getEmail(), "");
  EXPECT_EQ(student.getPhone(), "");
}

// Test setting and getting maximum length strings
TEST(StudentTest, SetMaxLengthStrings)
{
  std::string maxString(255, 'a'); // 255 'a' characters

  Student student;
  student.setNumber(maxString);
  student.setName(maxString);
  student.setSurname(maxString);
  student.setDepartment(maxString);
  student.setYear(maxString);
  student.setEmail(maxString);
  student.setPhone(maxString);

  EXPECT_EQ(student.getNumber(), maxString);
  EXPECT_EQ(student.getName(), maxString);
  EXPECT_EQ(student.getSurname(), maxString);
  EXPECT_EQ(student.getDepartment(), maxString);
  EXPECT_EQ(student.getYear(), maxString);
  EXPECT_EQ(student.getEmail(), maxString);
  EXPECT_EQ(student.getPhone(), maxString);
}

// Test setting and getting special characters
TEST(StudentTest, SetSpecialCharacters)
{
  Student student;
  student.setNumber("!@#$%^&*()");
  student.setName("Name with spaces");
  student.setSurname("O'Neil");
  student.setDepartment("Dept-123");
  student.setYear("Year!2024");
  student.setEmail("email+filter@example.com");
  student.setPhone("+1-123-456-7890");

  EXPECT_EQ(student.getNumber(), "!@#$%^&*()");
  EXPECT_EQ(student.getName(), "Name with spaces");
  EXPECT_EQ(student.getSurname(), "O'Neil");
  EXPECT_EQ(student.getDepartment(), "Dept-123");
  EXPECT_EQ(student.getYear(), "Year!2024");
  EXPECT_EQ(student.getEmail(), "email+filter@example.com");
  EXPECT_EQ(student.getPhone(), "+1-123-456-7890");
}

// Test invalid email format
TEST(StudentTest, SetInvalidEmail)
{
  Student student;
  student.setEmail("invalid-email");

  // Assuming that invalid emails are still accepted by the system
  // because validation logic is not implemented in the setter method.
  EXPECT_EQ(student.getEmail(), "invalid-email");
}
