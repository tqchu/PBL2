#ifndef PERCENTAGE
#define PERCENTAGE

/** 
 * Dùng để lưu phần trăm khi thống kê doanh thu.
*/

template <typename T>
class Percentage{
    private:
    T t;
    double percentage;
    public:
        Percentage();
        Percentage(const T &t, double percentage);
        T getT() const;
        double getPercentage() const;

        static void printTitle();

        void setT(const T &m);
        void setPercentage(double percentage);

        bool operator==(const Percentage &p) const;

        template <typename U>
        friend ostream& operator << (ostream & out, const Percentage<U> &p);

};
template <typename T>
Percentage<T>::Percentage(){
    percentage = 0;
}
template <typename T>
Percentage<T>::Percentage(const T &t, double percentage){
    this->t = t;
    this->percentage = percentage;
}
template <typename T>
void Percentage<T>::printTitle(){
    T::printTitle();
    cout << setw(8) << "%";
}
template <typename T>
T Percentage<T>::getT() const{
    return this->t;
}
template <typename T>
double Percentage<T>::getPercentage() const{
    return this->percentage;
}

template <typename T>
void Percentage<T>::setT(const T &m){
    t = m;
}
template <typename T>
void Percentage<T>::setPercentage(double percentage){
    this->percentage = percentage;
}
template <typename T>
bool Percentage<T>::operator==(const Percentage &p) const{
    return t == p.t;
}
template <typename T>
ostream & operator << (ostream & out, const Percentage<T> &p){
    cout << p.t;
    cout << fixed << setprecision(2) << p.percentage;
    return out;
}


#endif