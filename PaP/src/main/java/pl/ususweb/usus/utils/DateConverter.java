package pl.ususweb.usus.utils;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

@Component
public class DateConverter {

    private static String format;

    @Value("${usus.dateFormat}")
    public void setNameStatic(String f){
        DateConverter.format = f;
    }

    // parses date using usus date format from properties
    public static LocalDate parseDate(String toParse){

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern(format);
        return LocalDate.parse(toParse,formatter);
    }
}
