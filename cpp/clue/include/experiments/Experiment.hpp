#ifndef CLUE_EX_EX
#define CLUE_EX_EX

#include "Linalg.hpp"
#include "dd/Package.hpp"

using namespace std;

enum ExperimentType {
    CLUE,       // Experiment will reduce with CLUE and then iterate
    DDSIM,      // Experiment will reduce with DD and then iterate
    DIRECT,     // Experiment will reduce with DIRECT and then iterate
    DDSIM_ALONE // Experiment will run the iteration on DD without reduction
};

ExperimentType ExperimentType_fromString(string);
string ExperimentType_toString(ExperimentType);

/**
 * Class that define an interface for experiments. 
 * 
 * This class is abstract and the methods required for an experiment to work are the pure virtual methods.
*/
class Experiment {
    protected: 
        /** ABSTRACT METHODS FOR AN EXPERIMENT **/
        /* Method to get the number of q-bits for the experiment*/
        virtual luint size() = 0;
        /* Method to get the correct size of the lumping for this experiment */
        virtual luint correct_size() = 0;
        /* Method to get a quivk bound for the lumping size */
        virtual luint bound_size() = 0;
        /* Method to compute the direct lumping of the experiment (usually faster) */
        virtual array<dd::CMat, 2U> direct() = 0;
        /**
         *  Method to obtain the matrix to apply a lumping.
         * 
         * This matrix (in the case of QAOA) will be the problem matrix.
        */
        virtual vector<CCSparseVector> matrix() = 0;
        /* Method to obtain the REDUCED begin matrix (if necessary) */
        virtual dd::CMat matrix_B(dd::CMat&) = 0;
        /**
         * Method to obtain a quantum computation to apply a lumping.
         * 
         * This method obtains the "problem" circuit in the case of QAOA.
        */
        virtual qc::QuantumComputation* quantum(double) = 0;
        /* Method to obtain the BEGIN circuit (if necessary) */
        virtual qc::QuantumComputation* quantum_B(double) = 0;
        /* Method to change the type of experiment */
        virtual Experiment* change_exec_type(ExperimentType) = 0;

        // Protected attributes
        string name;            // Name of the experiment
        string observable;      // String representing the observable for the lumping
        luint iterations;       // Number of iterations to perform in an experiment.
        ExperimentType type;    // Type of the experiment. Depending on the type, different methods will be run
        dd::Package<>* package; // dd::Package with the cache information for the size for  whole execution.

        /* Execution attributes */
        bool executed = false;  // Flag indicating if the experiment has been executed or not
        double red_ratio = 1.0; // The reduction ratio obtained in the execution. If no reduction, the value is 1.
        double red_time = -1.0; // Execution time of the reduction.
        double it_time = -1.0;  // Execution time of the iteration.
        double tot_time = -1.0;  // Execution time of the iteration.
        double mem_used = -1.0; // Memory usage of the execution
 
        // Protected methods
        /* Method to get the observable for use with CLUE */
        virtual CCSparseVector clue_observable();
        /* Method to get the observable for use with DD */
        virtual dd::vEdge dd_observable(); // TODO Currently not working

    private:
        /* Method that runs the CLUE reduction (only used when this->type == CLUE) */
        void run_clue();
        /* Method that runs the DDSIM reduction (only used when this->type == DDSIM) */
        void run_ddsim();
        /* Method that runs the DIRECT reduction (only used when this->type == DIRECT) */
        void run_direct();
        /* Method that runs the CLUE reduction (only used when this->type == DDSIM_ALONE) */
        void run_ddsim_alone();

    public:
        /** CONSTRUCTORS **/
        Experiment(string eName, string eObservable, luint eIterations, ExperimentType eType, dd::Package<>* ePackage) { 
            this->name = eName; 
            this->observable = eObservable; 
            this->iterations = eIterations; 
            this->type = eType; 
            this->package = ePackage;
        }
        
        virtual ~Experiment() = default;
        /* Method that runs the experiment */
        void run();
        /* Method to clean the execution run */
        void clean_exec() { this->executed = false; }
        /* Method to get the string out of an experiment */
        virtual string to_string() = 0;
        /* Method that generate the CSV row for this experiment */
        string to_csv(char = ',');

        /* Method to get the total execution time */
        double total_time() { return this->tot_time; }
        /* Method to get the total execution time */
        double reduction_ratio() { return this->red_ratio; }
        /* Method to get the total execution time */
        double reduction_time() { return this->red_time; }
        /* Method to get the total execution time */
        double iteration_time() { return this->it_time; }
};

#endif