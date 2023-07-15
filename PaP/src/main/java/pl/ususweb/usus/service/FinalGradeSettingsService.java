package pl.ususweb.usus.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import pl.ususweb.usus.Repository.FinalGradeSettingsRepository;
import pl.ususweb.usus.entity.FinalGradeSettings;

@Service
public class FinalGradeSettingsService {

    @Autowired
    private FinalGradeSettingsRepository finalGradeSettingsRepository;
    public void saveSettings(FinalGradeSettings settings){
        settings.setId(0);
        finalGradeSettingsRepository.saveAndFlush(settings);
    }

    public FinalGradeSettings getFinalGradeSettings(){
        return finalGradeSettingsRepository.findById(0).orElse(null);
    }


}
