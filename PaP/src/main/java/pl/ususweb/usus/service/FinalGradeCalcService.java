package pl.ususweb.usus.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import pl.ususweb.usus.entity.FinalGradeSettings;
import pl.ususweb.usus.entity.Grade;
import pl.ususweb.usus.entity.GradedTest;
import pl.ususweb.usus.entity.Student;

import java.util.ArrayList;

@Service
public class FinalGradeCalcService {

    @Autowired
    private FinalGradeSettingsService finalGradeSettingsService;

    @Autowired
    private GradedTestService gradedTestService;

    public String pointsToFinalGrade(Float points){
        FinalGradeSettings settings = finalGradeSettingsService.getFinalGradeSettings();
        if (points<settings.getGrade3()){
            return "2";
        }
        else if (points<settings.getGrade35())
        {
            return "3";
        }
        else if (points<settings.getGrade4())
        {
            return "3,5";
        }
        else if (points<settings.getGrade45())
        {
            return "4";
        }
        else if (points<settings.getGrade5())
        {
            return "4,5";
        }
        else
        {
            return "5";
        }
    }

    public String finalGradeForStudent(Student s)
    {
        ArrayList<GradedTest> studentTests = (ArrayList<GradedTest>) gradedTestService.findGradedTestsByStudent(s);
        Float pointsum = 0.f;

        for (GradedTest test : studentTests){
            Grade g = gradedTestService.findGradeByGradedTestAndStudent(test,s);
            if (g!=null)
            {
                pointsum+=g.getResult();
            }
        }

       return pointsToFinalGrade(pointsum);
    }

}
