import datetime


def check_if_leap_year(year):
    """Checks if a given year is a leap year.

    :param year: positive integer
    :return: boolean
    """
    if year % 4 != 0:
        return False
    elif year % 100 != 0:
        return True
    elif year % 400 != 0:
        return False
    else:
        return True


def check_if_leap_day_this_year(date):
    """Checks if a leap day has happened in the current year, before a given date.

    :param date: tuple (year, month, day)
    :return: boolean (True if a leap day has happened in the current year, False otherwise)
    """
    year = date[0]
    month = date[1]
    day = date[2]
    leap_day_this_year = False
    if check_if_leap_year(year):
        if month > 2 or (month == 2 and day == 29):
            leap_day_this_year = True
    return leap_day_this_year


def count_leap_days_since_year_zero(date):
    """Counts leap days since 1 Jan, year 0.

    :param date: tuple (year, month, day)
    :return: positive integer
    """
    year = date[0]
    divisible_by_4 = (year - 1) // 4 + 1
    divisible_by_100 = (year - 1) // 100 + 1
    divisible_by_400 = (year - 1) // 400 + 1
    leap_day_this_year = int(check_if_leap_day_this_year(date))
    return divisible_by_4 - divisible_by_100 + divisible_by_400 + leap_day_this_year


def count_days_since_year_zero(date):
    """Counts the total number of days since 1 Jan, year 0.

    :param date: tuple (year, month, day)
    :return: number of days (natural number)
    """
    months = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    sum_months = [0]
    for i in range(1, len(months)):
        sum_months.append(sum_months[i - 1] + months[i])
    year = date[0]
    month = date[1]
    day = date[2]
    days_before_this_year = year * 365
    leap_days = count_leap_days_since_year_zero(date)
    days_this_year = sum_months[month - 1] + day

    return days_before_this_year + leap_days + days_this_year


def count_days_since_birth(birth_date):
    """Counts the age of a person in days, given the birthdate, taking into account the birthdate and the current date.

    :param birth_date: tuple (year, month, day)
    :return: positive integer (number of days)
    """
    current_time = datetime.datetime.now()
    current_date = (current_time.year, current_time.month, current_time.day)
    return count_days_since_year_zero(current_date) - count_days_since_year_zero(birth_date) + 1


if __name__ == "__main__":
    print("Enter your birthdate")
    birth_year = int(input("Year: "))
    birth_month = int(input("Month: "))
    birth_day = int(input("Day: "))
    print("Days since birth:", count_days_since_birth((birth_year, birth_month, birth_day)))
