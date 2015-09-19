#include "Analyzer.h"
#include "gtest/gtest.h"

// Test of parsing a first bunch of news, get path of news and titles
TEST(Analyzer, toString) {
  Analyzer analyzer("../data_test");
  std::string expected("Ruta del directorio: ../data_test\n\n"
		  "Titulo:  Detenidos en Reino Unido dos adolescentes sospechosos de matar de un disparo a un menor \n\n"
		  "Titulo:  Detenidos cinco menores en relaci\xF3n con el asesinato de el ni\xF1o de Liverpool \n\n"
		  "Titulo:  Detienen a otro sospechoso de 15 a\xF1os por la muerte de el ni\xF1o de 11 en Liverpool \n\n"
		  "Titulo:  La polic\xED" "a pone en libertad a los sospechosos de el asesinato de el ni\xF1o de Liverpool \n\n"
		  "Titulo:  Liberan a los dos sospechosos de el asesinato de un ni\xF1o en Liverpool \n\n"
		  "Titulo:  Siguen los interrogatorios a los detenidos por el asesinato de el ni\xF1o de Liverpool \n\n"
		  "Titulo:  Detienen a seis j\xF3venes m\xE1s en relaci\xF3n con el asesinato de el ni\xF1o de Liverpool \n\n"
		  "Titulo:  Liberan a los dos sospechosos detenidos por el asesinato de un ni\xF1o de 11 a\xF1os en Liverpool \n\n");
  EXPECT_EQ(analyzer.toString(), expected);
}

// Test of a first bunch of news, group by entity
TEST(Analyzer, newsGroupByEntity) {
  Analyzer analyzer("../data_test");

  std::string expected("\nJones\n"
		  "*[ Detenidos en Reino Unido dos adolescentes sospechosos de matar de un disparo a un menor ]\n\n"
		  "Liverpool\n"
		  "*[ Liberan a los dos sospechosos de el asesinato de un ni\xF1o en Liverpool ]\n"
		  "*[ Detienen a seis j\xF3venes m\xE1s en relaci\xF3n con el asesinato de el ni\xF1o de Liverpool ]\n\n"
		  "Polic\xED" "a\n"
		  "*[ Detienen a otro sospechoso de 15 a\xF1os por la muerte de el ni\xF1o de 11 en Liverpool ]\n\n"
		  "Rhys\n"
		  "*[ Detenidos cinco menores en relaci\xF3n con el asesinato de el ni\xF1o de Liverpool ]\n"
		  "*[ La polic\xED" "a pone en libertad a los sospechosos de el asesinato de el ni\xF1o de Liverpool ]\n"
		  "*[ Siguen los interrogatorios a los detenidos por el asesinato de el ni\xF1o de Liverpool ]\n"
		  "*[ Liberan a los dos sospechosos detenidos por el asesinato de un ni\xF1o de 11 a\xF1os en Liverpool ]\n");
  EXPECT_EQ(analyzer.groupNews(), expected);
}

// Test of a first bunch of news, group by references
TEST(Analyzer, newsGroupByReference) {
  Analyzer analyzer("../data_test");

  std::string expected("[ Detenidos en Reino Unido dos adolescentes sospechosos de matar de un disparo a un menor ]\n"
		  "   *[ Liberan a los dos sospechosos de el asesinato de un ni\xF1o en Liverpool ]\n"
		  "   *[ Detienen a seis j\xF3venes m\xE1s en relaci\xF3n con el asesinato de el ni\xF1o de Liverpool ]\n"
		  "   *[ Detienen a otro sospechoso de 15 a\xF1os por la muerte de el ni\xF1o de 11 en Liverpool ]\n"
		  "   *[ Detenidos cinco menores en relaci\xF3n con el asesinato de el ni\xF1o de Liverpool ]\n"
		  "   *[ La polic\xED" "a pone en libertad a los sospechosos de el asesinato de el ni\xF1o de Liverpool ]\n"
		  "   *[ Siguen los interrogatorios a los detenidos por el asesinato de el ni\xF1o de Liverpool ]\n"
		  "   *[ Liberan a los dos sospechosos detenidos por el asesinato de un ni\xF1o de 11 a\xF1os en Liverpool ]\n\n");
  EXPECT_EQ(analyzer.groupGeneralNews(), expected);
}

