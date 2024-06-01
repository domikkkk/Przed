package pl.projektpis.sklep.entity;

import com.datastax.oss.driver.api.core.uuid.Uuids;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import org.springframework.data.cassandra.core.mapping.PrimaryKey;
import org.springframework.data.cassandra.core.mapping.Table;
import org.springframework.data.cassandra.core.mapping.UserDefinedType;

import java.util.Base64;
import java.util.UUID;

@Table
//@AllArgsConstructor
//@NoArgsConstructor
@Getter // potrzebne do RestController
@UserDefinedType //needed to allow List<Product> in basket
public class Product {

    public Product(String nazwa, String opis, Double cena, Double waga, String wymiary, String image_base64)
    {
        this.image_base64 = image_base64;
        this.id = Uuids.timeBased();
        this.nazwa = nazwa;
        this.opis = opis;
        this.cena = cena;
        this.waga = waga;
        this.wymiary = wymiary;
    }

    @PrimaryKey
    UUID id;

    private String nazwa;
    private String opis;
    private Double cena;
    private Double waga;
    private String wymiary;
    private String image_base64;
}
