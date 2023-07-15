package pl.ususweb.usus;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.context.event.ApplicationReadyEvent;
import org.springframework.context.event.EventListener;
import pl.ususweb.usus.entity.FinalGradeSettings;
import pl.ususweb.usus.service.FinalGradeSettingsService;

@SpringBootApplication
public class UsusApplication {

	public static void main(String[] args) {
		SpringApplication.run(UsusApplication.class, args);
	}

	@Autowired
	FinalGradeSettingsService service;

	@EventListener(ApplicationReadyEvent.class)
	public void prepareFinalGrade() {
		FinalGradeSettings settings = service.getFinalGradeSettings();
		if (settings==null)
		{
			// create default
			settings = new FinalGradeSettings(0,"PAP 22L",50.f,60.f,70.f,80.f,90.f);
			service.saveSettings(settings);
		}

	}

}


