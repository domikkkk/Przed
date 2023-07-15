package pl.ususweb.usus.entity;


import lombok.*;

import javax.persistence.*;

@Entity
@AllArgsConstructor
@NoArgsConstructor
@Setter
@Getter
public class FinalGradeSettings {
    @Id
    private Integer id;

    String courseName;

    Float grade3;
    Float grade35;
    Float grade4;
    Float grade45;
    Float grade5;

}
