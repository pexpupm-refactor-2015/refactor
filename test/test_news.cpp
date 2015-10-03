#include "Analyzer.h"
#include "JsonTuitParser.h"
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

// Test of parsing a first bunch of news, get path of news and titles
TEST(Analyzer, toStringAllData) {
  Analyzer analyzer("../data");
  std::string expected("Ruta del directorio: ../data\n\n"
  "Titulo:  Dean pierde fuerza a el adentrar se en M\xE9xico \n\n"
  "Titulo:  Dean pasa a ser tormenta tropical \n\n"
  "Titulo:  ' Dean ' provoca otros tres muertos antes de extinguir se en el interior de M\xE9xico \n\n"
  "Titulo:  El hurac\xE1n Dean podr\xED" "a cobrar fuerza a el volver a las aguas c\xE1lidas de el Golfo de M\xE9xico \n\n"
  "Titulo:  ' Dean ' deja Yucat\xE1n debilitado pero podr\xED" "a fortalecerse en el Golfo de M\xE9xico \n\n"
  "Titulo:  El hurac\xE1n Dean baja a categor\xED" "a 1 tras atravesar el Yucat\xE1n mexicano \n\n"
  "Titulo:  El ' Dean ' se debilita y en las pr\xF3ximas horas podr\xED" "a convertir se en tormenta tropical \n\n"
  "Titulo:  Las lluvias y vientos devastadores de el Dean se sienten ya en la costa oeste de M\xE9xico \n\n"
  "Titulo:  ' Dean ' llega a el Caribe mexicano convertido en un hurac\xE1n ' potencialmente catastr\xF3" "fico ' \n\n"
  "Titulo:  M\xE1s de 400.000 evacuados en Cuba ante la amenaza de inundaciones por el ' Dean ' \n\n"
  "Titulo:  Evacuadas de Nahar a el Bared las familias de los milicianos de Fatah a el Islam \n\n"
  "Titulo:  L\xED" "bano toma el control de Naher a el Bared \n\n"
  "Titulo:  El Ej\xE9rcito de el L\xED" "bano anuncia la muerte en combate de el l\xED" "der de Fatah a el Islam \n\n"
  "Titulo:  Evacuan de Nahr a el Bared a las familias de los milicianos de Fatah a el Islam \n\n"
  "Titulo:  a el Fatah refuerza la seguridad en el campo de refugiados palestinos de Ain el Helu \n\n"
  "Titulo:  El ex primer ministro Sharif volver\xE1 a Pakist\xE1n el 10 de septiembre para medir se a Musharraf \n\n"
  "Titulo:  El Tribunal Supremo permite a Sharif , ex primer ministro de Pakist\xE1n , volver de el exilio \n\n"
  "Titulo:  Bhutto anuncia que regresar\xE1 \" muy pronto \" a Pakist\xE1n \n\n"
  "Titulo:  La ex primera ministra paquistan\xED Bhutto anuncia que regresar\xE1 ' muy pronto ' de el exilio \n\n"
  "Titulo:  Baja participaci\xF3n en las elecciones marroqu\xED" "es \n\n"
  "Titulo:  Los nacionalistas Istiqlal ganan las elecciones en Marruecos \n\n"
  "Titulo:  Los observadores piden a Rabat acometer reformas para alentar la participaci\xF3n \n\n"
  "Titulo:  El Gobierno marroqu\xED prev\xE9 que la participaci\xF3n electoral alcance el 41 % \n\n"
  "Titulo:  Los islamista moderados , favoritos en los comicios legislativos que celebra hoy Marruecos \n\n"
  "Titulo:  Los marroqu\xED" "es votan hoy con los islamistas moderados como favoritos \n\n"
  "Titulo:  Los islamistas moderados acarician la victoria en las elecciones parlamentarias en Marruecos \n\n"
  "Titulo:  Guatemala inicia la recta final de la campa\xF1" "a electoral \n\n"
  "Titulo:  Guatemala vota en medio de la peor ola de violencia de las \xFAltimas d\xE9" "cadas \n\n"
  "Titulo:  Los dos principales candidatos a la Presidencia de Guatemala cierran sus campa\xF1" "as \n\n"
  "Titulo:  Asesinan a tiros a dos candidatos locales de el partido de Rigoberta Mench\xFA en Guatemala \n\n"
  "Titulo:  ' La mejor madre de el mundo ' \n\n"
  "Titulo:  Numerosos actos recuerdan a Diana a los 10 a\xF1os de su muerte \n\n"
  "Titulo:  Camila no ir\xE1 a el funeral por Diana \n\n"
  "Titulo:  Buscan supervivientes entre las ruinas de el mayor atentado en Irak desde 2003 \n\n"
  "Titulo:  M\xE1s de 200 muertos en Irak en el ataque m\xE1s sangriento desde 2003 \n\n"
  "Titulo:  Ch\xE1vez se reunir\xE1 en Caracas con delegados de las FARC \n\n"
  "Titulo:  Ch\xE1vez anuncia ante \xC1lvaro Uribe que recibir\xE1 en Venezuela a un enviado de las FARC \n\n"
  "Titulo:  Las FARC rechazan el ofrecimiento de Ch\xE1vez de liberar rehenes en Venezuela \n\n"
  "Titulo:  Ch\xE1vez llega a Bogot\xE1 para entrevistar se con Uribe sobre los secuestrados de las FARC \n\n"
  "Titulo:  Ch\xE1vez llega a Bogot\xE1 para mediar en la liberaci\xF3n de secuestrados por las FARC \n\n"
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

//Test of a first bunch of news, group by entity
TEST(Analyzer, newsGroupByEntityAllData)
{
  Analyzer analyzer("../data");
  std::string expected("\nBhutto\n*[ La ex primera ministra paquistan\xED Bhutto anuncia que regresar\xE1 \' muy pronto \' de el exilio ]\n\n"
  "Ch\xE1vez\n*[ Ch\xE1vez llega a Bogot\xE1 para entrevistar se con Uribe sobre los secuestrados de las FARC ]\n*[ Ch\xE1vez llega a Bogot\xE1 para mediar en la liberaci\xF3n de secuestrados por las FARC ]\n\n"
  "Cuba\n*[ M\xE1s de 400.000 evacuados en Cuba ante la amenaza de inundaciones por el \' Dean \' ]\n\n"
  "Dean\n*[ El hurac\xE1n Dean podr\xED" "a cobrar fuerza a el volver a las aguas c\xE1lidas de el Golfo de M\xE9xico ]\n*[ El hurac\xE1n Dean baja a categor\xED" "a 1 tras atravesar el Yucat\xE1n mexicano ]\n*[ El \' Dean \' se debilita y en las pr\xF3ximas horas podr\xED" "a convertir se en tormenta tropical ]\n\n"
  "Diana\n*[ \' La mejor madre de el mundo \' ]\n*[ Numerosos actos recuerdan a Diana a los 10 a\xF1os de su muerte ]\n\n"
  "Ej\xE9rcito\n*[ Evacuan de Nahr a el Bared a las familias de los milicianos de Fatah a el Islam ]\n\n"
  "FARC\n*[ Ch\xE1vez se reunir\xE1 en Caracas con delegados de las FARC ]\n*[ Ch\xE1vez anuncia ante \xC1lvaro Uribe que recibir\xE1 en Venezuela a un enviado de las FARC ]\n*[ Las FARC rechazan el ofrecimiento de Ch\xE1vez de liberar rehenes en Venezuela ]\n\n"
  "Fatah\n*[ El Ej\xE9rcito de el L\xED" "bano anuncia la muerte en combate de el l\xED" "der de Fatah a el Islam ]\n*[ a el Fatah refuerza la seguridad en el campo de refugiados palestinos de Ain el Helu ]\n\n"
  "Gobierno\n*[ Baja participaci\xF3n en las elecciones marroqu\xED" "es ]\n\n"
  "Hajj\n*[ Evacuadas de Nahar a el Bared las familias de los milicianos de Fatah a el Islam ]\n\n"
  "Iglesia\n*[ Guatemala inicia la recta final de la campa\xF1" "a electoral ]\n\n"
  "Interior\n*[ El Gobierno marroqu\xED prev\xE9 que la participaci\xF3n electoral alcance el 41 % ]\n\n"
  "Irak\n*[ M\xE1s de 200 muertos en Irak en el ataque m\xE1s sangriento desde 2003 ]\n\n"
  "Jones\n*[ Detenidos en Reino Unido dos adolescentes sospechosos de matar de un disparo a un menor ]\n\n"
  "Liverpool\n*[ Liberan a los dos sospechosos de el asesinato de un ni\xF1o en Liverpool ]\n*[ Detienen a seis j\xF3venes m\xE1s en relaci\xF3n con el asesinato de el ni\xF1o de Liverpool ]\n\n"
  "L\xED" "bano\n*[ L\xED" "bano toma el control de Naher a el Bared ]\n\n"
  "Marruecos\n*[ Los observadores piden a Rabat acometer reformas para alentar la participaci\xF3n ]\n\n"
  "M\xE9xico\n*[ Dean pierde fuerza a el adentrar se en M\xE9xico ]\n*[ Dean pasa a ser tormenta tropical ]\n*[ \' Dean \' deja Yucat\xE1n debilitado pero podr\xED" "a fortalecerse en el Golfo de M\xE9xico ]\n*[ \' Dean \' llega a el Caribe mexicano convertido en un hurac\xE1n \' potencialmente catastr\xF3" "fico \' ]\n\n"
  "Nacional\n*[ Los islamista moderados , favoritos en los comicios legislativos que celebra hoy Marruecos ]\n*[ Guatemala vota en medio de la peor ola de violencia de las \xFAltimas d\xE9" "cadas ]\n\n"
  "Nobel\n*[ Asesinan a tiros a dos candidatos locales de el partido de Rigoberta Mench\xFA en Guatemala ]\n\n"
  "PJD\n*[ Los nacionalistas Istiqlal ganan las elecciones en Marruecos ]\n*[ Los islamistas moderados acarician la victoria en las elecciones parlamentarias en Marruecos ]\n\n"
  "Pakist\xE1n\n*[ Bhutto anuncia que regresar\xE1 \" muy pronto \" a Pakist\xE1n ]\n\n"
  "Partido\n*[ Los marroqu\xED" "es votan hoy con los islamistas moderados como favoritos ]\n\n"
  "Polic\xED" "a\n*[ Detienen a otro sospechoso de 15 a\xF1os por la muerte de el ni\xF1o de 11 en Liverpool ]\n\n"
  "Princesa\n*[ Camila no ir\xE1 a el funeral por Diana ]\n\n"
  "Puebla\n*[ \' Dean \' provoca otros tres muertos antes de extinguir se en el interior de M\xE9xico ]\n\n"
  "P\xE9rez\n*[ Los dos principales candidatos a la Presidencia de Guatemala cierran sus campa\xF1" "as ]\n\n"
  "Rhys\n*[ Detenidos cinco menores en relaci\xF3n con el asesinato de el ni\xF1o de Liverpool ]\n*[ La polic\xED" "a pone en libertad a los sospechosos de el asesinato de el ni\xF1o de Liverpool ]\n*[ Siguen los interrogatorios a los detenidos por el asesinato de el ni\xF1o de Liverpool ]\n*[ Liberan a los dos sospechosos detenidos por el asesinato de un ni\xF1o de 11 a\xF1os en Liverpool ]\n\n"
  "Sharif\n*[ El ex primer ministro Sharif volver\xE1 a Pakist\xE1n el 10 de septiembre para medir se a Musharraf ]\n*[ El Tribunal Supremo permite a Sharif , ex primer ministro de Pakist\xE1n , volver de el exilio ]\n\n"
  "Sinyar\n*[ Buscan supervivientes entre las ruinas de el mayor atentado en Irak desde 2003 ]\n\n"
  "Yucat\xE1n\n*[ Las lluvias y vientos devastadores de el Dean se sienten ya en la costa oeste de M\xE9xico ]\n");
  EXPECT_EQ(analyzer.groupNews(), expected);
}

// Test of a first bunch of news, group by references
TEST(Analyzer, newsGroupByReferenceAllData) {
  Analyzer analyzer("../data");
  std::string expected("[ La ex primera ministra paquistan\xED Bhutto anuncia que regresar\xE1 ' muy pronto ' de el exilio ]\n"
  "   *[ Ch\xE1vez llega a Bogot\xE1 para entrevistar se con Uribe sobre los secuestrados de las FARC ]\n"
  "   *[ Ch\xE1vez llega a Bogot\xE1 para mediar en la liberaci\xF3n de secuestrados por las FARC ]\n"
  "   *[ Ch\xE1vez se reunir\xE1 en Caracas con delegados de las FARC ]\n"
  "   *[ Ch\xE1vez anuncia ante \xC1lvaro Uribe que recibir\xE1 en Venezuela a un enviado de las FARC ]\n"
  "   *[ Las FARC rechazan el ofrecimiento de Ch\xE1vez de liberar rehenes en Venezuela ]\n"
  "   *[ Detenidos en Reino Unido dos adolescentes sospechosos de matar de un disparo a un menor ]\n"
  "   *[ Bhutto anuncia que regresar\xE1 \" muy pronto \" a Pakist\xE1n ]\n"
  "   *[ El ex primer ministro Sharif volver\xE1 a Pakist\xE1n el 10 de septiembre para medir se a Musharraf ]\n"
  "   *[ El Tribunal Supremo permite a Sharif , ex primer ministro de Pakist\xE1n , volver de el exilio ]\n"
  "\n"
  "[ Ch\xE1vez llega a Bogot\xE1 para entrevistar se con Uribe sobre los secuestrados de las FARC ]\n"
  "   *[ Ch\xE1vez llega a Bogot\xE1 para mediar en la liberaci\xF3n de secuestrados por las FARC ]\n"
  "   *[ Ch\xE1vez se reunir\xE1 en Caracas con delegados de las FARC ]\n"
  "   *[ Ch\xE1vez anuncia ante \xC1lvaro Uribe que recibir\xE1 en Venezuela a un enviado de las FARC ]\n"
  "   *[ Las FARC rechazan el ofrecimiento de Ch\xE1vez de liberar rehenes en Venezuela ]\n"
  "\n"
  "[ M\xE1s de 400.000 evacuados en Cuba ante la amenaza de inundaciones por el ' Dean ' ]\n"
  "   *[ El hurac\xE1n Dean podr\xED" "a cobrar fuerza a el volver a las aguas c\xE1lidas de el Golfo de M\xE9xico ]\n"
  "   *[ El hurac\xE1n Dean baja a categor\xED" "a 1 tras atravesar el Yucat\xE1n mexicano ]\n"
  "   *[ El ' Dean ' se debilita y en las pr\xF3ximas horas podr\xED" "a convertir se en tormenta tropical ]\n"
  "   *[ Los islamista moderados , favoritos en los comicios legislativos que celebra hoy Marruecos ]\n"
  "   *[ Guatemala vota en medio de la peor ola de violencia de las \xFAltimas d\xE9" "cadas ]\n"
  "\n"
  "[ El hurac\xE1n Dean podr\xED" "a cobrar fuerza a el volver a las aguas c\xE1lidas de el Golfo de M\xE9xico ]\n"
  "   *[ El hurac\xE1n Dean baja a categor\xED" "a 1 tras atravesar el Yucat\xE1n mexicano ]\n"
  "   *[ El ' Dean ' se debilita y en las pr\xF3ximas horas podr\xED" "a convertir se en tormenta tropical ]\n"
  "   *[ M\xE1s de 400.000 evacuados en Cuba ante la amenaza de inundaciones por el ' Dean ' ]\n"
  "   *[ Dean pierde fuerza a el adentrar se en M\xE9xico ]\n"
  "   *[ Dean pasa a ser tormenta tropical ]\n"
  "   *[ ' Dean ' deja Yucat\xE1n debilitado pero podr\xED" "a fortalecerse en el Golfo de M\xE9xico ]\n"
  "   *[ ' Dean ' llega a el Caribe mexicano convertido en un hurac\xE1n ' potencialmente catastr\xF3" "fico ' ]\n"
  "   *[ ' Dean ' provoca otros tres muertos antes de extinguir se en el interior de M\xE9xico ]\n"
  "   *[ Las lluvias y vientos devastadores de el Dean se sienten ya en la costa oeste de M\xE9xico ]\n"
  "\n"
  "[ ' La mejor madre de el mundo ' ]\n"
  "   *[ Numerosos actos recuerdan a Diana a los 10 a\xF1os de su muerte ]\n"
  "   *[ Camila no ir\xE1 a el funeral por Diana ]\n"
  "\n"
  "[ Evacuan de Nahr a el Bared a las familias de los milicianos de Fatah a el Islam ]\n"
  "   *[ El Ej\xE9rcito de el L\xED" "bano anuncia la muerte en combate de el l\xED" "der de Fatah a el Islam ]\n"
  "   *[ a el Fatah refuerza la seguridad en el campo de refugiados palestinos de Ain el Helu ]\n"
  "   *[ Evacuadas de Nahar a el Bared las familias de los milicianos de Fatah a el Islam ]\n"
  "   *[ L\xED" "bano toma el control de Naher a el Bared ]\n"
  "   *[ Los islamista moderados , favoritos en los comicios legislativos que celebra hoy Marruecos ]\n"
  "   *[ Guatemala vota en medio de la peor ola de violencia de las \xFAltimas d\xE9" "cadas ]\n"
  "\n"
  "[ Ch\xE1vez se reunir\xE1 en Caracas con delegados de las FARC ]\n"
  "   *[ Ch\xE1vez anuncia ante \xC1lvaro Uribe que recibir\xE1 en Venezuela a un enviado de las FARC ]\n"
  "   *[ Las FARC rechazan el ofrecimiento de Ch\xE1vez de liberar rehenes en Venezuela ]\n"
  "   *[ Ch\xE1vez llega a Bogot\xE1 para entrevistar se con Uribe sobre los secuestrados de las FARC ]\n"
  "   *[ Ch\xE1vez llega a Bogot\xE1 para mediar en la liberaci\xF3n de secuestrados por las FARC ]\n"
  "\n"
  "[ El Ej\xE9rcito de el L\xED" "bano anuncia la muerte en combate de el l\xED" "der de Fatah a el Islam ]\n"
  "   *[ a el Fatah refuerza la seguridad en el campo de refugiados palestinos de Ain el Helu ]\n"
  "   *[ Evacuan de Nahr a el Bared a las familias de los milicianos de Fatah a el Islam ]\n"
  "\n"
  "[ Baja participaci\xF3n en las elecciones marroqu\xED" "es ]\n"
  "   *[ El Gobierno marroqu\xED prev\xE9 que la participaci\xF3n electoral alcance el 41 % ]\n"
  "   *[ Los observadores piden a Rabat acometer reformas para alentar la participaci\xF3n ]\n"
  "   *[ Los marroqu\xED" "es votan hoy con los islamistas moderados como favoritos ]\n"
  "\n"
  "[ Guatemala inicia la recta final de la campa\xF1" "a electoral ]\n"
  "   *[ Los dos principales candidatos a la Presidencia de Guatemala cierran sus campa\xF1" "as ]\n\n");
  EXPECT_EQ(analyzer.groupGeneralNews(), expected);
}

// Simple Test of Json Tuits parsing
TEST(Analyzer, JsonTuitsParser) {
  JsonTuitParser parser;
  std::vector<Tuit> tuits;
  parser.parseFile("../data_test_json/tuits.json", tuits);
  EXPECT_EQ(tuits.size(), 3);
  EXPECT_EQ(tuits[0].getId(), "0");
  EXPECT_EQ(tuits[0].getUser(), "@pepe_perez");
  EXPECT_EQ(tuits[0].getBody(), "Liberan a los dos sospechosos detenidos \
por el asesinato de un niño de 11 años en Liverpool");

  EXPECT_EQ(tuits[1].getId(), "1");
  EXPECT_EQ(tuits[1].getUser(), "@juan_toqui");
  EXPECT_EQ(tuits[1].getBody(), "Detienen a seis jóvenes más en relación con \
el asesinato de el niño de Liverpool");

  EXPECT_EQ(tuits[2].getId(), "2");
  EXPECT_EQ(tuits[2].getUser(), "@pupulupu");
  EXPECT_EQ(tuits[2].getBody(), "Siguen los interrogatorios a los detenidos \
por el asesinato de el niño de Liverpool");
}

TEST(Analyzer, toStringJson) {
  Analyzer analyzer("../data_test_json");
  std::string expected("Ruta del directorio: ../data_test_json\n\n"
		  "Titulo:  Detenidos en Reino Unido dos adolescentes sospechosos de matar de un disparo a un menor \n\n"
		  "Titulo:  Detenidos cinco menores en relaci\xF3n con el asesinato de el ni\xF1o de Liverpool \n\n"
		  "Titulo:  Detienen a otro sospechoso de 15 a\xF1os por la muerte de el ni\xF1o de 11 en Liverpool \n\n"
		  "Titulo:  La polic\xED" "a pone en libertad a los sospechosos de el asesinato de el ni\xF1o de Liverpool \n\n"
		  "Titulo:  Liberan a los dos sospechosos de el asesinato de un ni\xF1o en Liverpool \n\n"
		  "Titulo:  Siguen los interrogatorios a los detenidos por el asesinato de el ni\xF1o de Liverpool \n\n"
		  "Titulo:  Detienen a seis j\xF3venes m\xE1s en relaci\xF3n con el asesinato de el ni\xF1o de Liverpool \n\n"
		  "Titulo:  Liberan a los dos sospechosos detenidos por el asesinato de un ni\xF1o de 11 a\xF1os en Liverpool \n\n"
		  "Titulo: \n\n"
		  "Titulo: \n\n"
		  "Titulo: \n\n");
  EXPECT_EQ(analyzer.toString(), expected);
}

TEST(Analyzer, toWideStringJson) {
  Analyzer analyzer("../data_test_json");
  std::string expected("Ruta del directorio: ../data_test_json\n\n"
                       "Titulo:  Detenidos en Reino Unido dos adolescentes sospechosos de matar de un disparo a un menor \n\n"
                       "Cuerpo:  Un ni\xF1o de 11 a\xF1os muri\xF3 anoche de un tiro en el cuello en un aparcamiento de Liverpool despu\xE9s de haber jugado a f\xFAtbol  Dos adolescentes brit\xE1nicos han sido arrestados en relaci\xF3n con la muerte a tiros de un ni\xF1o de 11 a\xF1os de edad cuando estaba en un aparcamiento de Liverpool donde hab\xED" "a estado jugando a f\xFAtbol , ha anunciado la polic\xED" "a .  Los detenidos , de 14 y 18 a\xF1os , est\xE1n siendo interrogados por la polic\xED" "a bajo la sospecha de asesinato , ha declarado una portavoz de la polic\xED" "a .  Rhys Jones muri\xF3 por los disparos recibidos ayer por la noche en el aparcamiento de un ' pub ' en la zona de Croxteth . Varios medios se\xF1" "alan que un joven en bicicleta , con la cara cubierta por una capucha , efectu\xF3 los disparos . En total se efectuaron tres disparos , pero s\xF3lo uno alcanz\xF3 , en el cuello , a Jones .  El jefe de polic\xED" "a , Bernard Hogan-Howe , ha declarado que Jones es una v\xED" "ctima inocente . \" Tanto \xE9l como su familia son miembros destacados de la comunidad \" , relat\xF3 el oficial a la cadena de televisi\xF3n Sky News . M\xE1s de 100 agentes est\xE1n investigando los hechos .  Reino Unido vive estos d\xED" "as varios episodios de violencia juvenil lo que ha llevado a el Gobierno de Brown a adoptar medidas de prevenci\xF3n . \r \n\n"
                       "Titulo:  Detenidos cinco menores en relaci\xF3n con el asesinato de el ni\xF1o de Liverpool \n\n"
                       "Cuerpo:  Rhys Jones muri\xF3 el pasado mi\xE9rcoles tras recibir un impacto de bala en el cuello cuando jugaba a el f\xFAtbol con unos amigos  La polic\xED" "a brit\xE1nica ha anunciado hoy la detenci\xF3n de otros cinco j\xF3venes , de quince a diecinueve a\xF1os , entre ellos dos muchachas , en relaci\xF3n con el asesinato de un ni\xF1o de once a\xF1os el pasado 22 de agosto en Liverpool ( norte de Inglaterra ) . El peque\xF1o , Rhys Jones , muri\xF3 cuando jugaba a el f\xFAtbol con unos amigos a el recibir el impacto de una bala en el cuello disparada por un adolescente encapuchado que iba montado en bicleta .  El suceso ha conmocionado a el Reino Unido por su brutalidad , y tanto la madre de el ni\xF1o , que tuvo a \xE9ste entre sus brazos mientras se desangraba sin poder hacer nada por salvar le , como la polic\xED" "a han hecho un llamamiento a los ciudadanos para que ayuden a atrapar a el asesino .  Seg\xFAn el perfil divulgado por la polic\xED" "a , \xE9se podr\xED" "a ser un menor de trece a quince a\xF1os , de piel blanca , de aproximadamente 1,70 de estatura y que en el momento de cometer el crimen llevaba ropa negra y calzado deportivo blanco . Los inspectores que investigan lo ocurrido han pedido a los testigos de el crimen que se presenten y les han asegurado que se proteger\xE1 su identidad cuando testifiquen .  Un centenar de agentes trabajan directamente en el caso , apoyados por otros colegas de la unidad de cr\xEDmenes con armas de fuego de el condado de Merseyside , a el que pertenece Liverpool . La polic\xED" "a est\xE1 examinando el material filmado por las c\xE1maras de v\xED" "deo instaladas en las proximidades de el lugar donde ocurri\xF3 el crimen .  Dos muchachos , de catorce y dieciocho a\xF1os , detenidos anteriormente por la polic\xED" "a , fueron puestos en libertad el jueves por la noche tras ser sometidos a interrogatorio .  Esta tarde , los jugadores de el equipo de el peque\xF1o asesinado , el Everton , de la primera divisi\xF3n inglesa , saldr\xE1n a el campo con brazaletes negros en el partido que juegan en casa contra el Blackburn Rovers . \r \n\n"
                       "Titulo:  Detienen a otro sospechoso de 15 a\xF1os por la muerte de el ni\xF1o de 11 en Liverpool \n\n"
                       "Cuerpo:  Anteriormente , las fuerzas de el orden hab\xED" "an arrestado a 10 j\xF3venes en relaci\xF3n con el crimen , si bien todos han sido puestos en libertad . \xBB  Un ni\xF1o de 15 a\xF1os fue detenido en relaci\xF3n con la muerte de el peque\xF1o Rhys Jones , quien recibi\xF3 un tiro en el cuello hace una semana en Liverpool ( norte de Inglaterra ) , inform\xF3 la Polic\xED" "a .  Rhys Jones , de 11 a\xF1os , muri\xF3 el pasado d\xED" "a 22 a el recibir el impacto de una bala cuando disputaba un partido de f\xFAtbol con varios amigos en el aparcamiento de un pub en el barrio de Croxteth .  Un portavoz de la Polic\xED" "a de el norte\xF1o condado de Merseyside precis\xF3 que el nuevo sospechoso fue detenido en ese barrio y ser\xE1 interrogado a lo largo de el d\xED" "a .  Anteriormente , las fuerzas de el orden hab\xED" "an arrestado a 10 j\xF3venes en relaci\xF3n con el crimen , que ha conmocionado a el Reino Unido , si bien todos han sido puestos en libertad .  Seg\xFAn la Polic\xED" "a , el ni\xF1o fue tiroteado por un adolescente encapuchado que paseaba en bicicleta por la zona . Los padres de Rhys hicieron este lunes un dram\xE1tico llamamiento a el homicida para que se entregue voluntariamente .  Melanie y Stephen Jones , de 41 y 44 a\xF1os , respectivamente , culparon a los padres de el asesino , a el que hasta ahora no ha identificado la Polic\xED" "a , por haber permitido que su hijo pudiese llegar a cometer un crimen tan horrendo .  Los jugadores de el Everton , equipo de la ' Premier League ' inglesa de el que Rhys era un forofo , se acercaron tambi\xE9n este lunes a el lugar donde el muchacho fue asesinado para rendir le un homenaje p\xF3stumo .  El club deposit\xF3 una corona de flores en forma de un bal\xF3n con sus colores - azul y blanco - , una camiseta y unas botas , en una especie de altar improvisado en el lugar de el crimen .  El otro equipo de la ciudad que milita en la ' Premier League ' , el Liverpool , entrenado por el espa\xF1ol Rafa Ben\xEDtez , tambi\xE9n homenaje\xF3 a el malogrado ni\xF1o antes de el partido de la previa de la Liga de Campeones que disput\xF3 este martes ante el Toulouse .  El asesinato coincidi\xF3 con un aumento de la violencia juvenil en las calles de el Reino Unido , que comienza a atemorizar a los adultos mientras los pol\xEDticos y la Polic\xED" "a abogan por tomar medidas urgentes antes de que la situaci\xF3n se escape a todo control . \r \n\n"
                       "Titulo:  La polic\xED" "a pone en libertad a los sospechosos de el asesinato de el ni\xF1o de Liverpool \n\n"
                       "Cuerpo:  La polic\xED" "a ha puesto en libertad sin cargos a cuatro de los sopechosos en relaci\xF3n con la muerte de Rhys Jones y los otros dos , en libertad condicional . \xBB  La polic\xED" "a de Liverpool ( noroeste de Inglaterra ) ha puesto en libertad a seis j\xF3venes a los que hab\xED" "a detenido en relaci\xF3n con el asesinato , la pasada semana , de un ni\xF1o de 11 a\xF1os , que recibi\xF3 un balazo en el cuello cuando regresaba de jugar a el f\xFAtbol con unos amigos .  Seg\xFAn confirmaron fuentes policiales , cuatro de los sospechosos , de edades comprendidas entre los 15 y los 19 a\xF1os y entre los que hab\xED" "a dos muchachas , fueron puestos en libertad sin cargos y los otros dos , en libertad condicional .  El peque\xF1o Rhys Jones muri\xF3 el pasado mi\xE9rcoles por la noche desangrado en brazos de su madre junto a el ' pub ' donde fue alcanzado por uno de los tres disparos que hizo un adolescente que iba en una bicicleta y de el que se sospecha que es miembro de una de las bandas locales .  El domingo , todas las iglesias de Liverpool efectuaron plegarias por el peque\xF1o , cuya muerte ha conmocionado a el pa\xEDs por la brutalidad y por reflejar un preocupante ambiente de violencia entre los j\xF3venes .  La ministra de el Interior , Jacqui Smith , ha anunciado que se pondr\xE1 a punto un sistema para la denuncia an\xF3nima de quienes posean ilegalmente armas de fuego y se crear\xE1 una red de puntos \" neutrales \" donde podr\xE1n entregar se pues , seg\xFAn dijo , lo importante es \" sacar las de la calle \" . \r \n\n"
                       "Titulo:  Liberan a los dos sospechosos de el asesinato de un ni\xF1o en Liverpool \n\n"
                       "Cuerpo:  La polic\xED" "a hace un nuevo llamamiento a la colaboraci\xF3n ciudadana para encontrar a el culpable  Los dos adolescentes detenidos ayer como sospechosos de haber matado de un disparo a un ni\xF1o de once a\xF1os en Liverpool , Inglaterra , fueron puestos en libertad esa misma noche , seg\xFAn ha informado hoy la polic\xED" "a . La b\xFAsqueda de el asesino sigue abierta . La sociedad brit\xE1nica est\xE1 conmocionada por este nuevo caso de violencia juvenil a el que hoy se le ha sumado una nueva v\xED" "ctima . Una joven de 20 a\xF1os ha fallecido como consecuencia de las heridas que le provoc\xF3 la paliza que le dio una banda juvenil en un parque de Lancashire , en el noroeste de el pa\xEDs , hace dos semanas  Los j\xF3venes arrestados por el asesinato , de l4 y 18 a\xF1os , fueron interrogados por los agentes antes de poner los en libertad . La v\xED" "ctima , Rhys Jones , de 11 a\xF1os , muri\xF3 el mi\xE9rcoles por la noche a el recibir un disparo en el cuello en un parking de un pub de el barrio de Croxteth , en Liverpool , donde hab\xED" "a estado jugando un partido de f\xFAtbol con varios amigos .  El principal sospechoso de el asesinato de el ni\xF1o es un adolescente de entre 13 y 15 a\xF1os de edad , blanco , de una altura aproximada de 1,70 metros , que vest\xED" "a ropa negra , iba encapuchado , calzaba unas deportivas blancas y que se paseaba por la zona en una bicicleta BMX negra , seg\xFAn ha detallado la polic\xED" "a . Las fuerzas de el orden han movilizado a unos cien agentes para investigar el caso .  Mensajes de m\xF3vil para dar pistas  La polic\xED" "a ha distribuido hoy por el condado de Mereseyside folletos con un n\xFAmero especial de tel\xE9" "fono para que los j\xF3venes de el barrio de Croxteth env\xED" "en mensajes de texto an\xF3nimos con pistas que puedan conducir a el responsable de el asesinato . \" La gente joven se manda mensajes de texto con frecuencia y queremos informaci\xF3n sobre el asesino \" , ha explicado el subcomisario de polic\xED" "a Simon Byrne a la BBC .  Las fuerzas de el orden , de hecho , est\xE1n \" decepcionadas \" por las pocas llamadas que han recibido de momento respecto a este caso . \" Hemos recibido algunas , pero no son suficientes \" , ha explicado la Ayudante de Comisario Patricia Gallan . \" Estoy decepcionada porque no estamos recibiendo m\xE1s . Por eso hago un llamamiento a los vecinos para que vengan y nos digan quien es el responsable \" , ha a\xF1" "adido Gallan .  La madre de el ni\xF1o , Melanie Jones , ha hecho un emocionado llamamiento a los ciudadanos para que ayuden a atrapar a el autor de el crimen . \" Nuestro hijo s\xF3lo ten\xED" "a once a\xF1os , s\xF3lo era un ni\xF1o . Esto no deber\xED" "a haber sucedido , no deber\xED" "a de estar ocurriendo . Por favor , ay\xFA" "dennos \" , ha dicho la madre sin poder contener las l\xE1grimas . \" Ustedes saben ah\xED afuera quien ha cometido este crimen , por favor , d\xEDgannos quien ha sido \" , ha a\xF1" "adido . Melanie , junto a su marido , Stephen , han acudido hoy a el escenario de el crimen para depositar unas flores y leer algunos de los mensajes que la gente ha dejado en el lugar .  EL primer ministro brit\xE1nico , Gord\xF3n Brown , conden\xF3 ayer el \" crimen atroz que ha conmocionado a todo el pa\xEDs \" y subray\xF3 que \" los responsables ser\xE1n encontrados , detenidos y castigados \" .  Muere una joven tras haber sido atacada por una banda  El triste suceso coincide con un debate sobre el aumento de la violencia juvenil en las calles de el Reino Unido , que comienza a atemorizar a los adultos mientras los pol\xEDticos y la Polic\xED" "a abogan por tomar medidas urgentes antes de que se escape a todo control .  Precisamente hoy se ha conocido el fallecimiento de Sophie Lancaster , una joven de 20 a\xF1os que se encontraba gravemente herida tras haber sido recibido una paliza , ella y su novio , por parte de una banda de j\xF3venes en un parque de Lancanshire . El ataque fue tan brutal que los agentes tuvieron dificultades para distinguir quien era el chico y quien la chica .  La polic\xED" "a , que cree que la pareja podr\xED" "a haber sido atacada por vestir ropa de estilo g\xF3tico , sigue sin tener pistas sobre los autores de la paliza , por eso han vuelto a hacer un llamamiento p\xFA" "blico para tener m\xE1s informaci\xF3n sobre el caso .  Desde comienzos de el 2007 , ocho menores han muerto a consecuencia de disparos de armas ligeras , seis de ellos en Londres , uno en Manchester y el \xFAltimo , Rhys Jones , en Liverpool . \r \n\n"
                       "Titulo:  Siguen los interrogatorios a los detenidos por el asesinato de el ni\xF1o de Liverpool \n\n"
                       "Cuerpo:  Seis jovenes contin\xFA" "an detenidos en relaci\xF3n con la muerte de Rhys Jones , un ni\xF1o de 11 a\xF1os alcanzado por una bala mientras jugaba a el f\xFAtbol en Liverpool . \xBB  LONDRES . - La polic\xED" "a brit\xE1nica contin\xFA" "a el interrogatorio de seis j\xF3venes en relaci\xF3n con el asesinato de Rhys Jones , un ni\xF1o de 11 a\xF1os alcanzado por una bala mientras jugaba a el f\xFAtbol en Liverpool ( norte de Inglaterra ) , suceso que por su brutalidad ha conmocionado a el Reino Unido .  Seis personas segu\xED" "an detenidas : dos muchachos de 15 y 16 , dos j\xF3venes de 19 , una muchacha de 15 y una joven de 18 a\xF1os , seg\xFAn los \xFAltimos datos de la polic\xED" "a , que ha puesto en libertad mientras tanto a un menor de 15 .  Dos j\xF3venes , de 14 y 18 a\xF1os , detenidos anteriormente por la polic\xED" "a , fueron puestos en libertad , el jueves por la noche tras ser sometidos a interrogatorio .  El s\xE1" "bado , 40.000 espectadores que asistieron a un partido de el club local , el Everton , de el que Jones era forofo , le rindieron tributo con un un\xE1nime aplauso de un minuto de duraci\xF3n .  Uno de los dos j\xF3venes de 19 a\xF1os detenidos por la polic\xED" "a es interrogado como sospechoso mientras que el otro se hiri\xF3 el s\xE1" "bado a el saltar por una ventana para escapar de la polic\xED" "a y ha tenido que ser tratado en un hospital .  La polic\xED" "a ha pedido la colaboraci\xF3n de una mujer a la que vieron pasear con un cochecito de ni\xF1o en las inmediaciones de el pub donde ocurri\xF3 el suceso y de la que se cree puede ser un importante testigo .  Seg\xFAn el perfil divulgado por la polic\xED" "a , \xE9se podr\xED" "a ser un menor de 13 a 15 a\xF1os , de piel blanca , de aproximadamente 1,70 de estatura y que en el momento de cometer el crimen llevaba ropa negra y calzado deportivo blanco .  Fuentes de la polic\xED" "a local aseguran que el asesino , que iba montado en una bicicleta , dio varias vueltas por detr\xE1s de el pub antes de hacer tres disparos con una pistola de ca\xF1\xF3n largo en la direcci\xF3n de Rhys , que fue alcanzado en el cuello por uno de ellos .  La polic\xED" "a ha pedido a los vecinos que rompan la muralla de silencio que rodea lo ocurrido , que venzan el miedo de declarar que parecen tener muchos y cuenten lo que han visto .  Los agentes han distribuido mientras tanto octavillas con un n\xFAmero de tel\xE9" "fono especial a el que los j\xF3venes pueden llamar o enviar an\xF3nimamente desde sus m\xF3viles mensajes con cualquier informaci\xF3n que pueda ayudar a dar con el homicida . \r \n\n"
                       "Titulo:  Detienen a seis j\xF3venes m\xE1s en relaci\xF3n con el asesinato de el ni\xF1o de Liverpool \n\n"
                       "Cuerpo:  La polic\xED" "a ha dado a conocer el posible perfil de el asesino que podr\xED" "a ser un menor de 13 a 15 a\xF1os , de piel blanca y de aproximadamente 1,70 de estatura . \xBB  La polic\xED" "a brit\xE1nica ha anunciado la detenci\xF3n de otros seis j\xF3venes , de 15 a 19 a\xF1os , entre ellos dos chicas , en relaci\xF3n con el asesinato de Rhys Jones , el ni\xF1o de 11 a\xF1os de Liverpool ( norte de Inglaterra ) .  Tres chicos de 15 , 16 , y 19 a\xF1os , m\xE1s dos chicas 15 y 18 fueron detenidos en Liverpool el s\xE1" "bado por la ma\xF1" "ana , seg\xFAn inform\xF3 un portavoz de la Polic\xED" "a de Merseyside dijo . Otro chico m\xE1s , de 19 a\xF1os fue , por la tarde .  El superintendente de la Polic\xED" "a , David Kelly , explic\xF3 que uno de los muchachos result\xF3 herido durante la detenci\xF3n , ya que se cay\xF3 de una ventana por la que intentaba escapar . La heridas que sufr\xED" "a no hicieron temer en ning\xFAn momento por su vida .  Rhys Jones muri\xF3 el mi\xE9rcoles por la noche cuando jugaba a el f\xFAtbol con unos amigos a el recibir el impacto de una bala en el cuello disparada por un adolescente encapuchado que iba montado en una bicicleta .  El suceso ha conmocionado a el Reino Unido por su brutalidad , y tanto la madre de el ni\xF1o , que tuvo a \xE9ste entre sus brazos mientras se desangraba sin poder hacer nada por salvar le , como la polic\xED" "a han hecho un llamamiento a los ciudadanos para que ayuden a atrapar a el asesino .  Seg\xFAn el perfil divulgado por la polic\xED" "a , \xE9se podr\xED" "a ser un menor de trece a quince a\xF1os , de piel blanca , de aproximadamente 1,70 de estatura y que en el momento de cometer el crimen llevaba ropa negra y calzado deportivo blanco .  Dos j\xF3venes , de 14 y 18 a\xF1os , detenidos anteriormente por la polic\xED" "a , fueron puestos en libertad , el jueves por la noche tras ser sometidos a interrogatorio .  Los inspectores que investigan lo ocurrido han pedido a los testigos de el crimen que se presenten y les han asegurado que se proteger\xE1 su identidad cuando testifiquen .  Los jugadores de el equipo de el peque\xF1o asesinado , el Everton , de la primera divisi\xF3n inglesa , saldr\xE1n a el campo con brazaletes negros en el partido que juegan en casa contra el Blackburn Rovers .  Un centenar de agentes trabajan directamente en el caso , apoyados por otros colegas de la unidad de cr\xEDmenes con armas de fuego de el condado de Merseyside , a el que pertenece Liverpool .  La polic\xED" "a est\xE1 examinando el material filmado por las c\xE1maras de v\xED" "deo instaladas en las proximidades de el lugar donde ocurri\xF3 el crimen . \r \n\n"
                       "Titulo:  Liberan a los dos sospechosos detenidos por el asesinato de un ni\xF1o de 11 a\xF1os en Liverpool \n\n"
                       "Cuerpo:  Rhys Jones muri\xF3 tras recibir el impacto de una bala en el cuello mientras jugaba un partido de f\xFAtbol con varios amigos en el aparcamiento de un pub . \xBB  Los dos adolescentes detenidos bajo sospecha de haber matado de un disparo a Rhys Jones , un ni\xF1o de 11 a\xF1os en Liverpool ( norte de Inglaterra ) han sido puestos en libertad , seg\xFAn ha confirmado la Polic\xED" "a , que sigue buscando a el asesino .  Los j\xF3venes , de 14 y 18 a\xF1os , fueron arrestados este jueves y liberados ese mismo d\xED" "a por la noche , tras ser interrogados sobre la muerte de el peque\xF1o Rhys Jones .  Rhys muri\xF3 el mi\xE9rcoles por la noche a el recibir el impacto de una bala en el cuello mientras disputaba un partido de f\xFAtbol con varios amigos en el aparcamiento de un pub en el barrio de Croxteth .  Seg\xFAn la Polic\xED" "a de el norte\xF1o condado de Merseyside , el ni\xF1o - de quien se han difundido fotos en las que viste la camiseta de el Everton , su club de f\xFAtbol preferido - fue tiroteado por un adolescente encapuchado que paseaba por la zona en una bicicleta .  Las fuerzas de el orden , que han movilizado a unos 100 agentes para investigar el caso , seg\xFAn ha divulgado una descripci\xF3n de el posible autor de el crimen , que ha conmocionado por su brutalidad a el Reino Unido .  Seg\xFAn ese perfil , el presunto asesino podr\xED" "a ser un menor de entre 13 y 15 a\xF1os de edad , blanco de piel , de aproximadamente 1,70 metros y ataviado con ropa negra y calzado deportivo blanco .  La madre de el ni\xF1o , Melanie Jones , cuyo hijo muri\xF3 en sus brazos mientras el personal de el servicio de ambulancias trataba de reanimarle , ha hecho un emocionado llamamiento a los ciudadanos para que ayuden a atrapar a el autor de el crimen .  \" Nuestro hijo s\xF3lo ten\xED" "a 11 a\xF1os , s\xF3lo era un ni\xF1o . Esto no deber\xED" "a haber sucedido . Esto no deber\xED" "a estar ocurriendo . Por favor , ay\xFA" "dennos \" , ha declarado la madre sin poder contener las l\xE1grimas . \" Sabemos que la gente debe estar asustada , pero no podemos dejar a el asesino suelto \" , ha agregado la madre .  La Polic\xED" "a de el condado de Merseyside reparti\xF3 folletos con un n\xFAmero especial de tel\xE9" "fono para que los j\xF3venes de el barrio de Croxteth env\xED" "en mensajes de texto an\xF3nimo con pistas que puedan conducir a el responsable de el asesinato .  \" La gente joven se manda mensajes de texto con frecuencia y queremos informaci\xF3n sobre el asesino \" , ha declarado el subcomisario de polic\xED" "a Simon Byrne a la cadena p\xFA" "blica brit\xE1nica BBC .  Por su parte , el Everton ( uno de los dos clubes de la ciudad que militan en la ' Premier League ' inglesa , junto a el Liverpool ) , de el que era hincha el peque\xF1o Rhys , le homenajear\xE1 el pr\xF3ximo s\xE1" "bado con un minuto de silencio antes de su partido ante el Blackburns Rovers .  Este jueves , el primer ministro brit\xE1nico , Gordon Brown , ha condenado el \" crimen atroz que ha conmocionado a todo el pa\xEDs \" , ha subrayado que \" los responsables ser\xE1n encontrados , detenidos y castigados \" y ha enviado su pesa me a la familia de el menor .  El triste suceso coincide con un debate sobre el aumento de la violencia juvenil en las calles de el Reino Unido , que comienza a atemorizar a los adultos mientras los pol\xEDticos y la Polic\xED" "a abogan por tomar medidas urgentes antes de que se escape a todo control .  Desde comienzos de el 2007 , ocho menores han muerto a consecuencia de disparos de armas ligeras , seis de ellos en Londres , uno en Manchester ( norte de Inglaterra ) y el \xFAltimo , el peque\xF1o Rhys Jones , en Liverpool . \r \n\n"
                       "Titulo: \n\n"
                       "Cuerpo: Liberan a los dos sospechosos detenidos por el asesinato de un ni\xF1o de 11 a\xF1os en Liverpool\n\n"
                       "Titulo: \n\n"
                       "Cuerpo: Detienen a seis j\xF3venes m\xE1s en relaci\xF3n con el asesinato de el ni\xF1o de Liverpool\n\n"
                       "Titulo: \n\n"
                       "Cuerpo: Siguen los interrogatorios a los detenidos por el asesinato de el ni\xF1o de Liverpool\n\n");
  EXPECT_EQ(analyzer.toWideString(), expected);
}
