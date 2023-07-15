package pl.ususweb.usus.entity;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import javax.persistence.*;
import java.time.LocalDate;
import java.util.List;

@AllArgsConstructor
@NoArgsConstructor
@Entity
@JsonIgnoreProperties({"re"})
@Table(name="Students")
@Setter
@Getter
public class Student {
    @Id
    @GeneratedValue
    private Integer indeks;

    private String firstname;

    private String lastname;

    private String username;

    private LocalDate birthdate;

    @ManyToMany
    @JoinTable(
            name = "students_groups",
            joinColumns = @JoinColumn(name = "indeks"),
            inverseJoinColumns = @JoinColumn(name = "id"))
    List<Group> studentGroups;

    @OneToMany
    List<ExchangeOffer> offers;


}