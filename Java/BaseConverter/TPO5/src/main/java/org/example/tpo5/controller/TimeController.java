package org.example.tpo5.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

import java.time.LocalDateTime;
import java.time.Year;
import java.time.ZoneOffset;
import java.time.format.DateTimeFormatter;

@Controller
public class TimeController {
    @RequestMapping("/current-time")
    @ResponseBody
    public String currentTime(@RequestParam(required = false, defaultValue = "0") String timeZone, @RequestParam(required = false, defaultValue = "HH:mm:ss.SSSS yyyy/MM/dd") String timeFormat){
        try{
            LocalDateTime now =  LocalDateTime.now(ZoneOffset.ofHours(Integer.parseInt(timeZone)));
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern(timeFormat);
            String dateTime = now.format(formatter);
            String[] dateTimeArr = dateTime.split(" ");
            return "<html>\n" +
                    "<head>\n" +
                    "    <meta charset=\"UTF-8\">\n" +
                    "    <title>Time and Date</title>\n" +
                    "    <link rel=\"stylesheet\" href=\"stylesheets/timeStyles.css\">\n" +
                    "</head>\n" +
                    "<body>\n" +
                    "<div class=\"container\">\n" +
                    "    <div class=\"time-section\">\n" +
                    "        <div class=\"frame-block\">\n" +
                    "            <h1><span class=\"frame\">Time</span>:</h1>\n" +
                    "        </div>\n" +
                    "        <div class=\"time-info\">\n" +
                    "            <h3 id=\"time\">"+ dateTimeArr[0] +"</h3>\n" +
                    "        </div>\n" +
                    "        <div class=\"time-image\">\n" +
                    "            <img src=\"images/clock.png\" alt=\"Time Image\" class=\"image\">\n" +
                    "        </div>\n" +
                    "    </div>\n" +
                    "    <div class=\"date-section\">\n" +
                    "        <div class=\"frame-block\">\n" +
                    "            <h1><span class=\"frame\">Date</span>:</h1>\n" +
                    "        </div>\n" +
                    "        <div class=\"date-info\">\n" +
                    "            <h3 id=\"date\">"+ dateTimeArr[1] +"</h3>\n" +
                    "        </div>\n" +
                    "        <div class=\"date-image\">\n" +
                    "            <img src=\"images/calendar.png\" alt=\"Date Image\" class=\"image\">\n" +
                    "        </div>\n" +
                    "    </div>\n" +
                    "</div>\n" +
                    "</body>\n" +
                    "</html>\n";

        } catch  (Exception e){
            LocalDateTime now = LocalDateTime.now();
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm:ss.SSSS yyyy/MM/dd");
            String dateTime = now.format(formatter);
            return "<html lang=\"en\">\n" +
                    "<head>\n" +
                    "    <meta charset=\"UTF-8\">\n" +
                    "    <title>Date and Time</title>\n" +
                    "    <link rel=\"stylesheet\" href=\"stylesheets/timeStyles.css\">\n" +
                    "</head>\n" +
                    "<body>\n" +
                    "<img src=\"images/error.png\" alt=\"Maths\" class=\"error-image\">\n" +
                    "<div class=\"error-container\">\n" +
                    "<br>"+
                    e.getMessage() +
                    "<div class=\"date-time\">\n"+
                    "<br>DEFAULT DATE AND TIME<br><br>" +
                    dateTime +
                    "</div>"+
                    "</div>"+
                    "</body>\n" +
                    "</html>\n";
        }
    }

    @RequestMapping("/current-year")
    @ResponseBody
    public String currentYear(){
        Year currentYear = Year.now();
        String year =  currentYear.toString();
        return "<html>\n" +
                "<head>\n" +
                "    <meta charset=\"UTF-8\">\n" +
                "    <title>Year</title>\n" +
                "    <link rel=\"stylesheet\" href=\"stylesheets/timeStyles.css\">\n" +
                "</head>\n" +
                "<body>\n" +
                "<div class=\"container\">\n" +
                "    <div class=\"year-section\">\n" +
                "        <div class=\"frame-block\">\n" +
                "            <h1><span class=\"frame\">Year: </span></h1>\n" +
                "        </div>\n" +
                "        <div class=\"year-info\">\n" +
                "            <div class=\"year\">"+ year +"</div>\n" +
                "        </div>\n" +
                "        <div class=\"year-image\">\n" +
                "            <img src=\"images/season.png\" alt=\"Year Image\" class=\"year-image\">\n" +
                "        </div>\n" +
                "    </div>\n" +
                "    </div>\n" +
                "</div>\n" +
                "</body>\n" +
                "</html>\n";
    }
}
