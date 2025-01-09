<?php

declare(strict_types=1);

use Rector\Config\RectorConfig;
use Rector\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector;

return RectorConfig::configure()
    ->withRules([RemoveUselessOverrideAttributeRector::class]);
