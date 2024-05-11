package org.example.tpo5.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;


@Controller
public class NumberController {

    private String[] digits = new String[100];
    @PostMapping("/convert")
    @ResponseBody
    public String convert(@RequestParam String num, @RequestParam int convertFrom, @RequestParam int convertTo){
        this.myChars();
        String initialNum = num;
        String convertedValue = "";
        String bin = "";
        String oct = "";
        String dec = "";
        String hex = "";
        boolean error = false;
        String errorMessage = "";
        String [] numDigits = num.split("");
        outerloop:
        for(int i = 0; i < numDigits.length; i++){
            for(int j = 0; j < digits.length; j++){
                if(numDigits[i].equals(digits[j])){
                    if(j > convertFrom - 1){
                        error = true;
                        errorMessage += "PROVIDED NUMBER IS NOT IN BASE " + convertFrom + ".<br>";
                        break outerloop;
                    }
                }
            }
        }
        if(convertFrom > 100 || convertFrom < 2){
            error = true;
            errorMessage += "WRONG INITIAL BASE. BASE OF THE SYSTEM MUST BE IN RANGE FROM 2 TO 100.<br>";
        }
        if(convertTo > 100 || convertTo < 2){
            error = true;
            errorMessage += "WRONG FINAL BASE. BASE OF THE SYSTEM MUST BE IN RANGE FROM 2 TO 100.<br>";
        }
        if(error){
            return "<html lang=\"en\">\n" +
                    "<head>\n" +
                    "    <meta charset=\"UTF-8\">\n" +
                    "    <title>Converter</title>\n" +
                    "    <link rel=\"stylesheet\" href=\"stylesheets/converterStyles.css\">\n" +
                    "</head>\n" +
                    "<body>\n" +
                    "<img src=\"images/error.png\" alt=\"Maths\" class=\"error-image\">\n" +
                    "<div class=\"error-container\">\n" +
                         errorMessage +
                    "</div>\n" +
                    "</body>\n" +
                    "</html>\n";
        }
        if(convertFrom == 10){
            convertedValue = convertFromDecimal(convertTo, initialNum);
            bin = convertFromDecimal(2, initialNum);
            oct = convertFromDecimal(8, initialNum);
            dec = convertFromDecimal(10, initialNum);
            hex = convertFromDecimal(16, initialNum);
        } else {
            // First, convert to decimal
            String decimalNum = convertToDecimal(convertFrom, initialNum);
            convertedValue = convertFromDecimal(convertTo, decimalNum);
            bin = convertFromDecimal(2, decimalNum);
            oct = convertFromDecimal(8, decimalNum);
            dec = convertFromDecimal(10, decimalNum);
            hex = convertFromDecimal(16, decimalNum);
        }
        return "<html lang=\"en\">\n" +
                "<head>\n" +
                "    <meta charset=\"UTF-8\">\n" +
                "    <title>Converter</title>\n" +
                "    <link rel=\"stylesheet\" href=\"stylesheets/converterStyles.css\">\n" +
                "</head>\n" +
                "<body>\n" +
                "<div class=\"converter-title\">Converter<div>\n" +
                "<img src=\"images/maths.png\" alt=\"Maths\" class=\"image\">\n" +
                "<div class=\"container\">\n" +
                "    <table>\n" +
                "        <tr>\n" +
                "            <td>Original value:</td>\n" +
                "            <td>"+ num +"</td>\n" +
                "        </tr>\n" +
                "        <tr>\n" +
                "            <td>Binary:</td>\n" +
                "            <td>"+ bin +"</td>\n" +
                "        </tr>\n" +
                "        <tr>\n" +
                "            <td>Octal:</td>\n" +
                "            <td>"+ oct +"</td>\n" +
                "        </tr>\n" +
                "        <tr>\n" +
                "            <td>Decimal:</td>\n" +
                "            <td>"+dec+"</td>\n" +
                "        </tr>\n" +
                "        <tr>\n" +
                "            <td>Hexadecimal:</td>\n" +
                "            <td>"+hex+"</td>\n" +
                "        </tr>\n" +
                "    </table>\n" +
                "</div>\n" +
                "</body>\n" +
                "</html>\n";
    }

    public String convertToDecimal(int convertFromBase, String num) {
        int converted = 0;
        String numStr = num.toLowerCase();
        int numDigits = numStr.length();
        for(int i = 0; i < numDigits; i++) {
            int digitValue = findInDigitsArray(numStr.charAt(i));
            converted += digitValue * Math.pow(convertFromBase, numDigits - 1 - i);
        }
        return Integer.toString(converted);
    }

    public void myChars(){
        int j = 48;
        for (int i = 0; i < 10; i++) {
            this.digits[i] = Character.toString((char) j);
            j+=1;
        }
        j = 97;
        for (int i = 0; i < 90; i++) {
            this.digits[i+10] = Character.toString((char) j);
            j+=1;
        }
    }

    public String convertFromDecimal(int convertToBase, String num){
        String converted = "";
        int intNum = Integer.parseInt(num);
        if(intNum == 0){
            return "0";
        }
        while(intNum > 0){
            int remainder = intNum % convertToBase;
            converted = digits[remainder] + converted;
            intNum/=convertToBase;
        }
        return converted;
    }

    private int findInDigitsArray(char digitChar) {
        String digitStr = String.valueOf(digitChar);
        for (int i = 0; i < this.digits.length; i++) {
            if (digitStr.equals(this.digits[i])) {
                return i;
            }
        }
        return -1;
    }

}
