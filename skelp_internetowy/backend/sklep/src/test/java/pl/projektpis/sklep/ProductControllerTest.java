package pl.projektpis.sklep;

import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.test.context.ActiveProfiles;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.web.servlet.MockMvc;
import pl.projektpis.sklep.controller.ProductsController;
import pl.projektpis.sklep.entity.Product;
import pl.projektpis.sklep.repository.ProductRepository;

import java.util.LinkedList;

import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.Assert.assertTrue;


//@SpringBootTest
@ActiveProfiles("test")
@RunWith(SpringRunner.class)
@WebMvcTest(ProductsController.class)
class ProductControllerTest {
    @Autowired
    ProductsController controller;

    @MockBean
    ProductRepository repo; // we don't want to test repository (because what's the point), so mock it with fake functionality

    @Autowired
    MockMvc mvc;

    @Test
    void testProductAdding()
    {
        LinkedList<Product> fakeRepo = new LinkedList<>();
        Product p = new Product("Produkt","produkt produktowy",20.0,100.0,"10x20x30","AEUIOP=");
        //mock the repo
        Mockito.when(repo.save(p)).thenAnswer(i -> {fakeRepo.add(p); return p;});
        Mockito.when(repo.findAll()).thenReturn(fakeRepo);

        controller.newProduct(p);
        LinkedList<Product> l = (LinkedList<Product>) controller.getAllProducts(null,null);
        System.out.println(l);
        assertTrue(l.contains(p));
    }
}
