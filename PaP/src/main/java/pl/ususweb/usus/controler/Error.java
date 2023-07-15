package pl.ususweb.usus.controler;


import org.springframework.boot.web.servlet.error.ErrorController;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


@Controller
public class Error implements ErrorController {
    @RequestMapping("/error")
    @GetMapping("/Exception")
    public String error(Model model, HttpServletRequest request, HttpServletResponse response){

        Exception exception = (Exception) request.getAttribute("javax.servlet.error.exception");
        int status = response.getStatus();
        model.addAttribute("exception", exception);
        model.addAttribute("statuscode", status);
        model.addAttribute("message", "Na a");
        return "errors";
    }
}
