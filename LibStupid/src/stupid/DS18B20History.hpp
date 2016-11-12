#ifndef CUTEHMI_LIBSTUPID_SRC_STUPID_DS18B20HISTORY_HPP
#define CUTEHMI_LIBSTUPID_SRC_STUPID_DS18B20HISTORY_HPP

#include "../platform.hpp"

#include "DS18B20HistoryWorker.hpp"

#include <charts/PointSeries.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace stupid {

class CUTEHMI_STUPID_API DS18B20History:
		public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(cutehmi::charts::PointSeries * series READ series NOTIFY seriesChanged)
		Q_PROPERTY(qint64 from READ from WRITE setFrom NOTIFY fromChanged)
		Q_PROPERTY(qint64 to READ to WRITE setTo NOTIFY toChanged)
		Q_PROPERTY(qint64 minimum READ minimum NOTIFY minimumChanged)
		Q_PROPERTY(qint64 maximum READ maximum NOTIFY maximumChanged)

		DS18B20History(std::unique_ptr<DS18B20HistoryWorker> worker = nullptr, QObject * parent = 0);

		~DS18B20History() override;

		charts::PointSeries * series() const;

		qint64 from() const;

		void setFrom(qint64 from);

		qint64 to() const;

		void setTo(qint64 to);

		/**
		 * Minimum. Retrieves maximum timestamp value.
		 * @return timestamp value for which historcal data starts to be available.
		 *
		 * @threadsafe
		 */
		qint64 minimum() const;

		/**
		 * Maximum. Retrieves minimum timestamp value.
		 * @return timestamp value of most recent historcal data that is available.
		 *
		 * @threadsafe
		 */
		qint64 maximum() const;

	public slots:
		void requestUpdate();

		void update();

	signals:
		void fromChanged();

		void toChanged();

		void seriesChanged();

		void minimumChanged();

		void maximumChanged();

	private:
		std::unique_ptr<DS18B20HistoryWorker> m_worker;
		charts::PointSeries * m_series;
		qint64 m_minimum;
		qint64 m_maximum;
		qint64 m_from;
		qint64 m_to;
};

}
}

#endif
