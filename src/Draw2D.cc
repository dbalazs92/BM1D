#include "Draw2D.hh"

Draw2D::Draw2D(int nop, double percent, int nRunsp, std::vector<Double_t> tp, std::vector<Double_t> xp) //int nop, double percent, int nRunsp, std::vector<Double_t> tp, std::vector<Double_t> xp
{
	t = tp;
	x = xp;
	nRuns = nRunsp;
	
	
	myAnalyse = new Analyse();
	myAnalyse -> AnalyseGaus(t,x);
	
	myCrusher = new Crusher(t,x);
	
	myLattice = new Lattice();
	
	myLattice -> SetNop(nop);
	myLattice -> SetPercent(percent*100);
	myLattice -> SetLattice(myAnalyse -> GetMu(), myAnalyse -> GetSigma());
	
	canvasB = new TCanvas("draw2Dcanv", "Lattice",800,400);
	canvasB -> Divide(2,1);
	
	canvasB2 = new TCanvas("draw2Dcanv2", "Lattice2",800,400);
	
	BM1D_histo = new TH2D("BM1D_histo", "BM1D_histo", myLattice -> GetWidth() , myLattice -> GetMuMin(), (myLattice -> GetMuMax()) , myLattice -> GetHeight() ,  myLattice -> GetSigmaMin(),  (myLattice -> GetSigmaMax()) );
	BM1D_histo2 = new TH2D("BM1D_histo2", "BM1D_histo2",  myLattice -> GetWidth() , myLattice -> GetMuMin(), (myLattice -> GetMuMax()) , myLattice -> GetHeight() ,  myLattice -> GetSigmaMin(),  (myLattice -> GetSigmaMax()) );
    gr = new TGraph();
	
	delete myAnalyse;
}

Draw2D::~Draw2D()
{
	canvasB->Clear();
	canvasB->Closed();
	delete canvasB;
	delete BM1D_histo;
	delete BM1D_histo2;
    
	canvasB2->Clear();
	canvasB2->Closed();
	delete canvasB2;
	delete gr;
	
	delete myLattice;
	delete myCrusher;
}

void Draw2D::Histo2D()
{
	double XbinSize = (myLattice -> GetMuMax() - myLattice -> GetMuMin())/ myLattice -> GetWidth() ;
	double YbinSize =( myLattice -> GetSigmaMax() -  myLattice -> GetSigmaMin() ) / myLattice -> GetHeight();
	
	double graphArrayX[myLattice -> GetLatticeSize()] = {};
	double graphArrayY[myLattice -> GetLatticeSize()] = {}; 
	
	std::cout << "maxSigma:" <<  myLattice -> GetSigmaMax() << std::endl;
	std::cout << "maxMu:" <<   myLattice -> GetMuMax() << std::endl;
	std::cout << "minSigma:" <<  myLattice -> GetSigmaMin() << std::endl;
	std::cout << "minMu:" <<   myLattice -> GetMuMin() << std::endl;
	
	for(int i = 0; i < 	(myLattice -> GetLatticeSize()); i++) 
		{
			std::cout<<"progress: "<<i<<"/"<<myLattice -> GetLatticeSize()<<"point\n";
			
			if(myCrusher -> RunMachine(nRuns, myLattice -> GetMuSigma(i)))
				{
					BM1D_histo -> Fill((i /  myLattice -> GetHeight()) * XbinSize + (XbinSize/2) + myLattice -> GetMuMin(),(i % myLattice -> GetHeight()) * YbinSize + (YbinSize/2) + myLattice -> GetSigmaMin() );
					BM1D_histo2 -> Fill((i /  myLattice -> GetHeight()) * XbinSize + (XbinSize/2) + myLattice -> GetMuMin(),(i % myLattice -> GetHeight()) * YbinSize + (YbinSize/2) + myLattice -> GetSigmaMin());
					
					graphArrayX[i] = (i /  myLattice -> GetHeight()) * XbinSize;
					graphArrayY[i] = (i % myLattice -> GetHeight()) * YbinSize;
						
				}
			
		}
	
			
	std::cout << "RunMachine done" << std::endl;
		
	//TGraph *gr = new TGraph(myLattice -> GetLatticeSize(),graphArrayX,graphArrayY);
	
	gr -> SetMarkerColor(46);	
	canvasB2 -> cd();
	//gr -> LineStyle()
	gr -> DrawGraph(myLattice -> GetLatticeSize(),graphArrayX,graphArrayY,"AP*");

	BM1D_histo -> SetMarkerStyle(kFullCircle);
	BM1D_histo-> SetMarkerStyle(21);
	canvasB -> cd(1);
	BM1D_histo -> Draw("PLC PMC");
	
	canvasB -> cd(2);	
	BM1D_histo2 -> Draw("COLZ");

	std::cout << "Histo done" << std::endl;
}