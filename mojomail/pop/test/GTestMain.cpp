// @@@LICENSE
//
//      Copyright (c) 2009-2012 Hewlett-Packard Development Company, L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// LICENSE@@@

#include <gtest/gtest.h>
#include "TestUtils.h"
#include "core/MojLogEngine.h"
#include "exceptions/ExceptionUtils.h"

int main(int argc, char** argv)
{
	MojObject config = QUOTE_JSON_OBJ((
		{"log": {"levels": {"session": "debug", "client": "debug", "protocol": "debug"}}}
	));
	MojLogEngine::instance()->configure(config, "test");

	std::set_terminate(&ExceptionUtils::TerminateHandler);

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
