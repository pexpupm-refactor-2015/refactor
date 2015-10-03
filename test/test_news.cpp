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
