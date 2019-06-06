#include <iostream>
#include <vector>
#include <assert.h>
#include <functional>

using namespace std;

struct Personne
{
	string myNom;
	string myPrenom;
	string myVille;
	unsigned short myAnneeNaissance;
	unsigned short myAnneeBac;
	static const unsigned short KAnneeNaissance = 1999;
	static const unsigned short KAnneeBac = 2017;
	static const unsigned short KAgeBac = 18;
	Personne(const string& nom = string(),
		const string& prenom = string(),
		const string& ville = string(),
		unsigned short anneeNaissance = KAnneeNaissance,
		unsigned short anneeBac = KAnneeBac) :
		myNom(nom), myPrenom(prenom), myVille(ville),
		myAnneeNaissance(anneeNaissance), myAnneeBac(anneeBac) {}
	string getNom(void) const { return myNom; }
	string getPrenom(void) const { return myPrenom; }
	string getVille(void) const { return myVille; }
	unsigned short getAnneeNaissance(void) const { return myAnneeNaissance; }
	unsigned short getAnneeBac(void) const { return myAnneeBac; }
	void setNom(const string& nom) { myNom = nom; }
	void setPrenom(const string& prenom) { myPrenom = prenom; }
	void setVille(const string& ville) { myVille = ville; }
	void setAnneeNaissance(unsigned short anneeNaissance)
	{
		myAnneeNaissance = anneeNaissance;
	} // setAnneeNaissance ( )
	void setAnneeBac(unsigned short anneeBac)
	{
		myAnneeBac = anneeBac;
	} // setAnneeBac ( )
}; // Personne

template<class InputIterator, class UnaryPredicate>
bool all_of(InputIterator first, InputIterator last, UnaryPredicate pred)
{
	while (first != last)
	{
		if (!pred(*first)) return false;
		++first;
	}
	return true;
}

template <typename Resul_t, typename Paramyt>
class IUnaryFunctor
{
public:
	virtual Resul_t operator ( ) (const Paramyt&) const = 0;
	virtual ~IUnaryFunctor(void) {}
}; // IUnaryFunctor

template <typename Resul_t, typename First_t, typename Second_t>
class IBinaryFunctor
{
public:
	typedef Resul_t result_type;
	typedef First_t first_argument_type;
	typedef Second_t second_argument_type;

	virtual Resul_t operator ( ) (const First_t&, const Second_t&) const = 0;
	virtual ~IBinaryFunctor(void) {}
}; // IB inaryFunctor

class Concitoyen : public IUnaryFunctor<bool, Personne> {
private:
	string myCommune;
public:
	Concitoyen(const string& commune) : myCommune(commune) {}

	virtual bool operator ( ) (const Personne& personne) const {
		return personne.getVille() == myCommune;
	}
};

void testUnaryFunction() {
	vector<Personne> personnes_Aix = { Personne("Nicolas", "GUERROUDJ", "Aix"), Personne("Kevin", "GUERROUDJ", "Aix"), Personne("David", "GUERROUDJ", "Aix") };
	assert(all_of(personnes_Aix.begin(), personnes_Aix.end(), Concitoyen("Aix")));
	vector<Personne> personnes_NotAix = { Personne("Matthis", "Houles", "Trets"), Personne("Marine", "LePen", "Arabie"), Personne("Jean", "Frederic", "Aix") };
	assert(!all_of(personnes_NotAix.begin(), personnes_NotAix.end(), Concitoyen("Aix")));
}

class ClasseDage : public IBinaryFunctor<bool, Personne, unsigned> {

public:
	virtual bool operator ( ) (const Personne& personne, const unsigned & annee) const {
		return personne.getAnneeNaissance() == annee || (personne.getAnneeNaissance() + personne.getAnneeBac()) == annee;
	}

};

void testBinaryFunction() {
	vector<Personne> personnes_1998 = { Personne("Nicolas", "GUERROUDJ", "Aix", 1998), Personne("Kevin", "GUERROUDJ", "Aix", 1998), Personne("David", "GUERROUDJ", "Aix", 1998) };
	assert(all_of(personnes_1998.begin(), personnes_1998.end(), bind2nd(ClasseDage(), 1998)));
}


	class IEditable;
	std::ostream& operator << (std::ostream& os, const IEditable& obj);

	class IEditable
	{
		virtual std::ostream& display(std::ostream& os) const = 0;
	public:
		virtual ~IEditable(void) {}
		friend std::ostream& operator << (std::ostream& os, const IEditable& obj);

	}; // IEditable
	enum {
		KNoExc = 0,
		KNoError = 0,
		KNotEnough = 249,
		KAlmostEmpty = 250,
		KUnknownRef = 252,
		KEmpty = 251,
		KFull = 253,
		KExcStd = 254,
		KExcInconnue = 255
	};

	class CException : public std::exception, public IEditable
	{
		std::string myLibelle;
		unsigned    myCodErr;

	public:
		CException(const std::string& libelle = std::string(),
			const unsigned      codErr = KNoExc)     noexcept;
		virtual ~CException(void)                            noexcept;

		const std::string& getLibelle(void) const           noexcept;
		unsigned            getCodErr(void) const           noexcept;

		virtual const char* what(void) const           noexcept;

	protected:
		virtual std::ostream& display(std::ostream& os) const;

	}; // CException


inline std::ostream& operator << (std::ostream& os, const IEditable& obj)
{
	return obj.display(os);
}

ostream& CException::display(ostream& os) const
{
	return os << "Exception : " << myLibelle << '\n'
		<< "Code      : " << myCodErr;

} // display()


#define CEXC CException

inline
CEXC::CException(const std::string& libelle /* = std::string () */,
	const unsigned      codErr  /* = KNoExc       */)
	noexcept
	: myLibelle(libelle), myCodErr(codErr) {}

inline const std::string& CEXC::getLibelle(void) const noexcept
{
	return myLibelle;

} // getLibelle()

unsigned CEXC::getCodErr(void) const noexcept { return myCodErr; }

CEXC::~CException(void) noexcept {}

const char* CEXC::what() const noexcept { return myLibelle.c_str(); }


class ExcStock : public CException{

private:
	unsigned myStock;
public: 
	const static unsigned KStockMin = 3;
	ExcStock(const string& libelle, const unsigned& codErr, const unsigned& reference) : CException(libelle, codErr), myStock(reference) {

	}

	virtual ~ExcStock(void) {

	}

	unsigned getReference(void) {
		return myStock;
	}

protected: 
	virtual ostream & display(ostream & os) {
		CException::display(os);
		os << "reference = " << getReference();
		return os;
	}

};

class Fournisseur {
private: 
	vector<unsigned> myReferences;
public:
	Fournisseur(void) noexcept : myReferences(vector<unsigned>()) {}

	void approvisionner(const unsigned& reference, const unsigned& quantite) {
		if (myReferences.size() > reference)
			myReferences[reference] += quantite;
		else if (myReferences.size() == reference) {
			try {
				myReferences.push_back(quantite);
			}
			catch (bad_alloc) {
				throw ExcStock("Vecteur plein", KFull, reference);
			}
		}
		else {
			throw ExcStock("Reference inconnu", KUnknownRef, reference);

		}
	}

	void commander(const unsigned& reference, const unsigned& quantite) {

		if (myReferences.size() > reference) {
			unsigned q = myReferences[reference];
			if (q < quantite) 
				throw ExcStock("Pas assez de quantité dans le stock", KNotEnough, reference);
			else if (q == quantite) {
				myReferences[reference] = 0;
				throw ExcStock("Stock vide !", KEmpty, reference);
			} else {
				myReferences[reference] -= quantite;
				if (myReferences[reference] < ExcStock::KStockMin)
					throw ExcStock("Stock presque vide !", KAlmostEmpty, reference);
			}
			myReferences[reference] += quantite;
		} else {
			throw ExcStock("Reference inconnu", KUnknownRef, reference);

		}
	}
};


void testFournisseur() {
	Fournisseur f;
	f.approvisionner(0, 10);
	f.approvisionner(1, 5);
	unsigned errCode = KNoError;
	try {
		f.approvisionner(5, 5);
	}catch (ExcStock exc) {
		errCode = exc.getCodErr();
	}
	catch (...) {}
	assert(errCode == KUnknownRef);
	f.approvisionner(0, 1);
	

	errCode = KNoError;
	try {
		f.commander(0, 10);
	}
	catch (ExcStock exc) {
		errCode = exc.getCodErr();
	}catch(...){}
	assert(errCode == KAlmostEmpty);


	errCode = KNoError;
	try {
		f.commander(0, 1);
	}
	catch (ExcStock exc) {
		errCode = exc.getCodErr();
	}
	catch (...) {}
	assert(errCode == KEmpty);


	errCode = KNoError;
	try {
		f.commander(0, 1);
	}
	catch (ExcStock exc) {
		errCode = exc.getCodErr();
	}
	catch (...) {}
	assert(errCode == KNotEnough);

	f.commander(1, 1);

	errCode = KNoError;
	try {
		f.commander(5, 5);
	}
	catch (ExcStock exc) {
		errCode = exc.getCodErr();
	}
	catch (...) {}
	assert(errCode == KUnknownRef);


 }

int main()
{
	testFournisseur();
	return 0;
}

