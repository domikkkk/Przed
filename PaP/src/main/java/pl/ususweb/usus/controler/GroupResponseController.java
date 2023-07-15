package pl.ususweb.usus.controler;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import pl.ususweb.usus.service.GroupService;

@Controller
@RequestMapping("/group")
public class GroupResponseController {

    @Autowired
    GroupService groupService;

    @GetMapping("/info/{groupId}") public String studentTimetable(@PathVariable Integer groupId, Model model)
    {

        model.addAttribute("group",groupService.getGroup(groupId));

        return "group_info";
    }
}
