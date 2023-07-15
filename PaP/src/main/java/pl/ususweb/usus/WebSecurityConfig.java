package pl.ususweb.usus;

import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.Customizer;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.web.SecurityFilterChain;
import org.springframework.context.annotation.Bean;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;


@Configuration
public class WebSecurityConfig {

	@Bean
	public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
		http.cors().and().csrf().disable()
            .headers().frameOptions().disable().and()
			.authorizeRequests()
				.anyRequest().fullyAuthenticated()
				.and()
			// .formLogin((form) -> form
                    // .loginPage("/login")
                    // .permitAll());
			.formLogin();

		return http.build();
	}

    @Value("${ldap.url}") private String ldapUrl;
    @Value("${ldap.managerDn}") private String managerDn;
    @Value("${ldap.managerPassword}") private String managerPassword;
    @Value("${ldap.userDnPatterns}") private String userDnPatterns;
    @Value("${ldap.groupSearchBase}") private String groupSearchBase;

	@Autowired
	public void configure(AuthenticationManagerBuilder auth) throws Exception {
		auth
			.ldapAuthentication()
				.userDnPatterns(userDnPatterns)
				.groupSearchBase(groupSearchBase)
				.contextSource()
					.url(ldapUrl)
                    .managerDn(managerDn)
                    .managerPassword(managerPassword)
					.and()
				.passwordCompare()
					.passwordEncoder(new BCryptPasswordEncoder())
					.passwordAttribute("userPassword");
	}

}
