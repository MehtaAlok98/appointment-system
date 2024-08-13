#include <gtest/gtest.h>
#include "core/Appointment.hpp"

// Test setting and getting the appointment details
TEST(AppointmentTest, SetAndGetDetails)
{
  Appointment appointment;
  appointment.setDate("2024-08-15");
  appointment.setStart("10:00");
  appointment.setEnd("11:00");

  EXPECT_EQ(appointment.getDate(), "2024-08-15");
  EXPECT_EQ(appointment.getStart(), "10:00");
  EXPECT_EQ(appointment.getEnd(), "11:00");
}

// Test setting and getting empty strings
TEST(AppointmentTest, SetEmptyStrings)
{
  Appointment appointment;
  appointment.setDate("");
  appointment.setStart("");
  appointment.setEnd("");

  EXPECT_EQ(appointment.getDate(), "");
  EXPECT_EQ(appointment.getStart(), "");
  EXPECT_EQ(appointment.getEnd(), "");
}

// Test setting and getting invalid time formats
TEST(AppointmentTest, SetInvalidTimeFormats)
{
  Appointment appointment;
  appointment.setStart("25:00");
  appointment.setEnd("24:60");

  // Assuming no validation in the setter methods
  EXPECT_EQ(appointment.getStart(), "25:00");
  EXPECT_EQ(appointment.getEnd(), "24:60");
}

// Test setting and getting special characters
TEST(AppointmentTest, SetSpecialCharacters)
{
  Appointment appointment;
  appointment.setDate("2024-08-15");
  appointment.setStart("10:00 AM");
  appointment.setEnd("11:00 PM");

  EXPECT_EQ(appointment.getDate(), "2024-08-15");
  EXPECT_EQ(appointment.getStart(), "10:00 AM");
  EXPECT_EQ(appointment.getEnd(), "11:00 PM");
}
