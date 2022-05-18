﻿using System;
using System.Globalization;
using System.Windows;
using System.Windows.Data;

namespace xDrive.App.Converters
{
    public class BooleanToVisibilityConverter : IValueConverter
    {
        private static object GetVisibility(object value)
        {
            if (value is not bool objValue)
                return Visibility.Collapsed;
            return objValue ? Visibility.Visible : Visibility.Collapsed;
        }

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return GetVisibility(value);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
