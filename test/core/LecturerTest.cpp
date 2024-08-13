#include <gtest/gtest.h>
#include "core/Lecturer.hpp"

// Test setting and getting the lecturer's chair
TEST(LecturerTest, SetAndGetChair)
{
  Lecturer lecturer;
  lecturer.setChair("Computer Science");
  EXPECT_EQ(lecturer.getChair(), "Computer Science");
}

// Test setting and getting empty strings
TEST(LecturerTest, SetEmptyStrings)
{
  Lecturer lecturer;
  lecturer.setNumber("");
  lecturer.setName("");
  lecturer.setSurname("");
  lecturer.setDepartment("");
  lecturer.setEmail("");
  lecturer.setPhone("");
  lecturer.setChair("");

  EXPECT_EQ(lecturer.getNumber(), "");
  EXPECT_EQ(lecturer.getName(), "");
  EXPECT_EQ(lecturer.getSurname(), "");
  EXPECT_EQ(lecturer.getDepartment(), "");
  EXPECT_EQ(lecturer.getEmail(), "");
  EXPECT_EQ(lecturer.getPhone(), "");
  EXPECT_EQ(lecturer.getChair(), "");
}

// Test setting and getting maximum length strings
TEST(LecturerTest, SetMaxLengthStrings)
{
  std::string maxString(255, 'a'); // 255 'a' characters

  Lecturer lecturer;
  lecturer.setNumber(maxString);
  lecturer.setName(maxString);
  lecturer.setSurname(maxString);
  lecturer.setDepartment(maxString);
  lecturer.setEmail(maxString);
  lecturer.setPhone(maxString);
  lecturer.setChair(maxString);

  EXPECT_EQ(lecturer.getNumber(), maxString);
  EXPECT_EQ(lecturer.getName(), maxString);
  EXPECT_EQ(lecturer.getSurname(), maxString);
  EXPECT_EQ(lecturer.getDepartment(), maxString);
  EXPECT_EQ(lecturer.getEmail(), maxString);
  EXPECT_EQ(lecturer.getPhone(), maxString);
  EXPECT_EQ(lecturer.getChair(), maxString);
}

// Test setting and getting special characters
TEST(LecturerTest, SetSpecialCharacters)
{
  Lecturer lecturer;
  lecturer.setNumber("!@#$%^&*()");
  lecturer.setName("Name with spaces");
  lecturer.setSurname("O'Neil");
  lecturer.setDepartment("Dept-123");
  lecturer.setEmail("email+filter@example.com");
  lecturer.setPhone("+1-123-456-7890");
  lecturer.setChair("Chair@Home");

  EXPECT_EQ(lecturer.getNumber(), "!@#$%^&*()");
  EXPECT_EQ(lecturer.getName(), "Name with spaces");
  EXPECT_EQ(lecturer.getSurname(), "O'Neil");
  EXPECT_EQ(lecturer.getDepartment(), "Dept-123");
  EXPECT_EQ(lecturer.getEmail(), "email+filter@example.com");
  EXPECT_EQ(lecturer.getPhone(), "+1-123-456-7890");
  EXPECT_EQ(lecturer.getChair(), "Chair@Home");
}
