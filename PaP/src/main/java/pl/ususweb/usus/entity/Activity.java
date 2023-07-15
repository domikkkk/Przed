package pl.ususweb.usus.entity;

import lombok.*;

import javax.persistence.*;
import java.util.List;

// Projekty, laboratoria, cwiczenia... cokolwiek co ma termin.
@Entity
@AllArgsConstructor
@Getter
@Setter
@NoArgsConstructor
public class Activity {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    Integer id;

    String name;
    String description;

    Boolean studentCanTrade;

    public Activity(String name, String description, Boolean studentCanTrade) {
        this.name = name;
        this.description = description;
        this.studentCanTrade = studentCanTrade;
    }

    @OneToMany(mappedBy = "activity", cascade = CascadeType.REMOVE)
    List<Group> activityGroups;

    @OneToMany(mappedBy = "activity", cascade = CascadeType.REMOVE)
    List<GradedTest> tests;

    @OneToMany(mappedBy = "activity", cascade = CascadeType.REMOVE)
    List<TradePeriod> tradePeriods;
}
