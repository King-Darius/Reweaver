/*
 * SPDX-License-Identifier: GPL-3.0-only
 * Audacity-CLA-applies
 *
 * Audacity
 * Music Composition & Notation
 *
 * Copyright (C) 2024 Audacity BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "cloudprojectsmodel.h"

#include "log.h"

using namespace muse;
using namespace au::project;

CloudProjectsModel::CloudProjectsModel(QObject* parent)
    : AbstractProjectsModel(parent)
{
}

void CloudProjectsModel::load()
{
    LOGW() << "MuseScore cloud integration is disabled; no remote projects will be loaded.";

    beginResetModel();
    m_items.clear();
    endResetModel();

    m_desiredRowCount = 0;

    setState(State::Error);
    emit hasMoreChanged();
}

void CloudProjectsModel::reload()
{
    load();
}

CloudProjectsModel::State CloudProjectsModel::state() const
{
    return m_state;
}

void CloudProjectsModel::setState(State state)
{
    if (m_state == state) {
        return;
    }

    m_state = state;
    emit stateChanged();
}

bool CloudProjectsModel::hasMore() const
{
    return false;
}

int CloudProjectsModel::desiredRowCount() const
{
    return m_desiredRowCount;
}

void CloudProjectsModel::setDesiredRowCount(int count)
{
    if (m_desiredRowCount == count) {
        return;
    }

    m_desiredRowCount = count;
    emit desiredRowCountChanged();
}
