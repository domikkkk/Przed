package pl.projektpis.sklep;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.context.event.ApplicationReadyEvent;
import org.springframework.context.event.EventListener;
import pl.projektpis.sklep.entity.Basket;
import pl.projektpis.sklep.repository.BasketRepository;

import java.util.UUID;

@SpringBootApplication
public class SklepApplication {

    //@Autowired
    //private BasketRepository basketRepository;

    public static void main(String[] args) {SpringApplication.run(SklepApplication.class, args);}


}
