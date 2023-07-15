package pl.ususweb.usus.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.servlet.view.RedirectView;
import pl.ususweb.usus.Repository.GroupRepository;
import pl.ususweb.usus.entity.Group;
import pl.ususweb.usus.entity.Student;
import pl.ususweb.usus.entity.TradePeriod;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

@Service
public class GroupService {
    @Autowired
    private GroupRepository groupRepository;

    @Autowired
    private TradePeriodService tradePeriodService;
    public void saveGroup(Group group){
        groupRepository.saveAndFlush(group);
    }

    public Group getGroup(Integer id){
        return groupRepository.findById(id).orElse(null);
    }

    public List<Group> getGroups(){
        return groupRepository.findAll();
    }

    public Set<Group> getTradeableGroupsForStudent(Student s) {
        ArrayList<Group> precheck = (ArrayList<Group>) groupRepository.findByActivity_StudentCanTradeTrue();
        HashSet<Group> valid = new HashSet<>();

        ArrayList<TradePeriod> tperiods = (ArrayList<TradePeriod>) tradePeriodService.getTradePeriods();

        for ( Group g : precheck){
            for (TradePeriod period : tperiods){
                if (period.getStartDate().isBefore(LocalDate.now()) && period.getEndDate().isAfter(LocalDate.now()) && s.getStudentGroups().contains(g)){
                    valid.add(g);
                }
            }
        }
        return valid;
    }

    public RedirectView removeGroup(Integer id){
        groupRepository.deleteById(id);
        return new RedirectView("/activity/list");
    }

    public Set<Group> getTradeableGroups() {

        ArrayList<Group> precheck = (ArrayList<Group>) groupRepository.findByActivity_StudentCanTradeTrue();
        Set<Group> valid = new HashSet<>();

        ArrayList<TradePeriod> tperiods = (ArrayList<TradePeriod>) tradePeriodService.getTradePeriods();

        for ( Group g : precheck){
            for (TradePeriod period : tperiods){
                if (period.getStartDate().isBefore(LocalDate.now()) && period.getEndDate().isAfter(LocalDate.now())){
                    valid.add(g);
                }
            }
        }
        return valid;
    }
}
